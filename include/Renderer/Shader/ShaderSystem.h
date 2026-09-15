#pragma once

#include "ShaderHandle.h"
#include "ShaderStage.h"
#include "ShaderCompiler.h"

#include "Core/Assets/ShaderAsset.h"

#ifndef VK_NO_PROTOTYPES
#define VK_NO_PROTOTYPES
#endif
#include <vulkan/vulkan.h>
#include <volk.h>

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class VulkanContext;

struct ShaderRuntimeEntryPoint
{
    ShaderStage Stage;
    std::string Name;
    VkShaderModule Module = VK_NULL_HANDLE;
};

struct Shader
{
    ShaderHandle Handle;
    std::string Path;
    std::vector<ShaderRuntimeEntryPoint> EntryPoints;
    // Keeps the asset (and its entry-point metadata) alive for the lifetime of
    // this compiled shader, so it stays resident in the AssetManager cache.
    std::shared_ptr<ShaderAsset> Asset;
    const ShaderRuntimeEntryPoint* GetEntryPoint(ShaderStage stage, const std::string& name="main") const;
};

class ShaderSystem
{
public:
    bool Initialize(VulkanContext& context);
    void Shutdown();

    ShaderHandle Load(const std::shared_ptr<ShaderAsset>& asset);

    Shader* Get(ShaderHandle handle);
    const Shader* Get(ShaderHandle handle) const;

    const ShaderRuntimeEntryPoint* GetEntryPoint(ShaderHandle shader, ShaderStage stage, const std::string& name="main") const;
    
    VkShaderModule GetModule(ShaderHandle shader, ShaderStage stage, const std::string& name="main") const;

    void Destroy(ShaderHandle handle);

private:
    std::vector<std::unique_ptr<Shader>> m_Shaders;
    std::unordered_map<AssetHandle, ShaderHandle, AssetHandleHash> m_AssetToShader;
    VulkanContext* m_Context{nullptr};
    ShaderCompiler m_Compiler;

    VkShaderModule CreateShaderModule(const std::vector<uint32_t>& spirv);
    void DestroyShaderModule(VkShaderModule module);

};
