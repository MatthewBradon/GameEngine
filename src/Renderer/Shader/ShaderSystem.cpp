#include "Renderer/Shader/ShaderSystem.h"
#include "Renderer/Vulkan/VulkanContext.h"
#include "Core/Log.h"

#include <algorithm>

const ShaderRuntimeEntryPoint* Shader::GetEntryPoint(ShaderStage stage, const std::string& name) const
{
    for (const auto& entryPoint : EntryPoints)
    {
        if (entryPoint.Stage == stage && entryPoint.Name == name)
        {
            return &entryPoint;
        }
    }

    ENGINE_WARN("Shader::GetEntryPoint() did not find entry point for stage: {} and name: {}", static_cast<int>(stage), name);

    return nullptr;
}

bool ShaderSystem::Initialize(VulkanContext& context)
{
    ENGINE_LOG("ShaderSystem::Initialize() called");

    m_Context = &context;

    if (!m_Compiler.Initialize())
    {
        ENGINE_ERROR("ShaderSystem::Initialize() failed to initialize shader compiler");
        return false;
    }

    return true;
}

void ShaderSystem::Shutdown()
{
    ENGINE_LOG("ShaderSystem::Shutdown() called");
    if(!m_Context)
    {
        ENGINE_WARN("ShaderSystem::Shutdown() called without a valid VulkanContext");
        return;
    }

    for (auto& shader: m_Shaders)
    {
        if (!shader)
        {
            continue;
        }

        for (auto& entryPoint : shader->EntryPoints)
        {
            DestroyShaderModule(entryPoint.Module);
        }
    }

    m_Shaders.clear();
    m_AssetToShader.clear();
    m_Compiler.Shutdown();
    m_Context = nullptr;
}

VkShaderModule ShaderSystem::CreateShaderModule(const std::vector<uint32_t>& spirv)
{
    VkShaderModuleCreateInfo createInfo {
        .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .codeSize = spirv.size() * sizeof(uint32_t),
        .pCode = spirv.data()
    };

    VkShaderModule module{VK_NULL_HANDLE};

    VULKAN_ASSERT(vkCreateShaderModule(m_Context->GetDevice(), &createInfo, nullptr, &module));

    return module;
}

void ShaderSystem::DestroyShaderModule(VkShaderModule module)
{
    if (module == VK_NULL_HANDLE)
    {
        ENGINE_WARN("ShaderSystem::DestroyShaderModule() called with VK_NULL_HANDLE");
        return;
    }

    vkDestroyShaderModule(m_Context->GetDevice(), module, nullptr);
}

ShaderHandle ShaderSystem::Load(const std::shared_ptr<ShaderAsset>& asset)
{
    ENGINE_LOG("ShaderSystem::Load() called for asset: {}", asset ? asset->GetPath() : "null");
    if (!asset)
    {
        ENGINE_ERROR("ShaderSystem::Load() called with null asset");
        return ShaderHandle{};
    }

    const AssetHandle& assetHandle = asset->GetHandle();

    auto existing = m_AssetToShader.find(assetHandle);

    if (existing != m_AssetToShader.end())
    {
        ENGINE_LOG("ShaderSystem::Load() found existing shader for asset: {}", asset->GetPath());
        return existing->second;
    }

    const std::string& path = asset->GetSourcePath();

    auto shader = std::make_unique<Shader>();

    ShaderHandle handle;

    handle.Index = static_cast<uint32_t>(m_Shaders.size());

    shader->Handle = handle;
    shader->Path = path;
    // Keep the asset alive so its entry-point metadata (and its cache entry)
    // remain valid for the lifetime of this compiled shader.
    shader->Asset = asset;

    for (const auto& entryPointDesc : asset->GetEntryPoints())
    {
        CompiledShader compiledShader;

        if (!m_Compiler.Compile(path, entryPointDesc.Stage, entryPointDesc.Name, compiledShader))
        {
            ENGINE_ERROR("ShaderSystem::Load() failed to compile shader: {} for entry point: {} stage: {}", path, entryPointDesc.Name, static_cast<int>(entryPointDesc.Stage));
            
            // If compilation fails, clean up any previously created shader modules for this shader before returning an invalid handle.
            for (const auto& entryPoint : shader->EntryPoints)
            {
                ENGINE_LOG("ShaderSystem::Load() cleaning up shader module for entry point: {} stage: {}", entryPoint.Name, static_cast<int>(entryPoint.Stage));
                DestroyShaderModule(entryPoint.Module);
            }

            return ShaderHandle{};
        }

        ENGINE_LOG("ShaderSystem::Load() successfully compiled shader: {} for entry point: {} stage: {}", path, entryPointDesc.Name, static_cast<int>(entryPointDesc.Stage));

        VkShaderModule module = CreateShaderModule(compiledShader.SpirV);

        ShaderRuntimeEntryPoint runtimeEntryPoint = {
            .Stage = compiledShader.Stage,
            .Name = compiledShader.EntryPoint,
            .Module = module
        };

        shader->EntryPoints.push_back(runtimeEntryPoint);
    }

    m_Shaders.push_back(std::move(shader));
    m_AssetToShader.emplace(assetHandle, handle);

    return handle;    
}

Shader* ShaderSystem::Get(ShaderHandle handle)
{
    if (!handle.IsValid())
    {
        ENGINE_WARN("ShaderSystem::Get() called with invalid handle: {}", handle.Index);
        return nullptr;
    }

    if (handle.Index >= m_Shaders.size())
    {
        ENGINE_WARN("ShaderSystem::Get() called with out-of-bounds handle: {}", handle.Index);
        return nullptr;
    }

    return m_Shaders[handle.Index].get();
}

const Shader* ShaderSystem::Get(ShaderHandle handle) const
{
    if (!handle.IsValid())
    {
        ENGINE_WARN("ShaderSystem::Get() called with invalid handle: {}", handle.Index);
        return nullptr;
    }

    if (handle.Index >= m_Shaders.size())
    {
        ENGINE_WARN("ShaderSystem::Get() called with out-of-bounds handle: {}", handle.Index);
        return nullptr;
    }

    return m_Shaders[handle.Index].get();
}

const ShaderRuntimeEntryPoint* ShaderSystem::GetEntryPoint(ShaderHandle shader, ShaderStage stage, const std::string& name) const
{
    const Shader* shaderPtr = Get(shader);

    if (!shaderPtr)
    {
        ENGINE_WARN("ShaderSystem::GetEntryPoint() called with invalid shader handle: {}", shader.Index);
        return nullptr;
    }

    return shaderPtr->GetEntryPoint(stage, name);
}

VkShaderModule ShaderSystem::GetModule(ShaderHandle shader, ShaderStage stage, const std::string& name) const
{
    const ShaderRuntimeEntryPoint* entryPoint = GetEntryPoint(shader, stage, name);

    if (!entryPoint)
    {
        ENGINE_WARN("ShaderSystem::GetModule() did not find entry point for shader handle: {}, stage: {}, name: {}", shader.Index, static_cast<int>(stage), name);
        return VK_NULL_HANDLE;
    }

    return entryPoint->Module;
}

void ShaderSystem::Destroy(ShaderHandle handle)
{
    if (!handle.IsValid())
    {
        ENGINE_WARN("ShaderSystem::Destroy() called with invalid handle: {}", handle.Index);
        return;
    }

    if (handle.Index >= m_Shaders.size())
    {
        ENGINE_WARN("ShaderSystem::Destroy() called with out-of-bounds handle: {}", handle.Index);
        return;
    }

    auto& shader = m_Shaders[handle.Index];

    if (!shader)
    {
        ENGINE_WARN("ShaderSystem::Destroy() called on already destroyed shader at index: {}", handle.Index);
        return;
    }

    for (auto& entryPoint : shader->EntryPoints)
    {
        DestroyShaderModule(entryPoint.Module);
    }

    // Find the asset handle associated with this shader and remove it from the map
    auto it = std::find_if(m_AssetToShader.begin(), m_AssetToShader.end(),
        [handle](const auto& pair) { return pair.second == handle; });

    if (it != m_AssetToShader.end())
    {
        ENGINE_LOG("ShaderSystem::Destroy() removing asset handle: {} for shader at index: {}", it->first.ToString(), handle.Index);
        m_AssetToShader.erase(it);
    }
    else
    {
        ENGINE_WARN("ShaderSystem::Destroy() could not find asset handle for shader at index: {}", handle.Index);
    }

    shader.reset();
}
