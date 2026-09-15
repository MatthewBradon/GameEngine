#include "Renderer/Shader/ShaderCompiler.h"
#include "Core/Log.h"
#include <slang.h>
#include <slang-com-ptr.h>

#include <array>

struct ShaderCompiler::Impl
{
    Slang::ComPtr<slang::IGlobalSession> GlobalSession;
    Slang::ComPtr<slang::ISession> Session;
};


// Pimpl: defined here, where Impl is complete, so unique_ptr<Impl> can be
// constructed and destroyed.
ShaderCompiler::ShaderCompiler() = default;

ShaderCompiler::~ShaderCompiler()
{
    if (m_Impl)
    {
        m_Impl->Session = nullptr;
        m_Impl->GlobalSession = nullptr;
    }
}


bool ShaderCompiler::Initialize()
{
    m_Impl = std::make_unique<Impl>();

    SlangResult result =
        slang::createGlobalSession(
            m_Impl->GlobalSession.writeRef());

    if (SLANG_FAILED(result))
    {
        m_Impl.reset();
        return false;
    }

    slang::TargetDesc targetDesc{};
    targetDesc.format = SLANG_SPIRV;
    targetDesc.profile = m_Impl->GlobalSession->findProfile("spirv_1_5");

    slang::SessionDesc sessionDesc{};
    sessionDesc.targets = &targetDesc;
    sessionDesc.targetCount = 1;

    result = m_Impl->GlobalSession->createSession(
            sessionDesc,
            m_Impl->Session.writeRef()
        );

    if (SLANG_FAILED(result))
    {
        m_Impl->GlobalSession = nullptr;
        m_Impl->Session = nullptr;

        m_Impl.reset();

        return false;
    }

    return true;
}

void ShaderCompiler::Shutdown()
{
    ENGINE_LOG("ShaderCompiler::Shutdown() called");
    if (!m_Impl)
    {
        ENGINE_WARN("ShaderCompiler::Shutdown() called but not initializated");
        return;
    }

    m_Impl->Session = nullptr;
    m_Impl->GlobalSession = nullptr;
    
    m_Impl.reset();       
}

inline SlangStage ConvertShaderStage(ShaderStage stage)
{
    switch (stage)
    {
        case ShaderStage::Vertex: return SLANG_STAGE_VERTEX;
        case ShaderStage::Fragment: return SLANG_STAGE_FRAGMENT;
        case ShaderStage::Compute: return SLANG_STAGE_COMPUTE;
        default:
            ENGINE_ERROR("ConvertShaderStage() received unknown ShaderStage: {}", static_cast<int>(stage));
            return SLANG_STAGE_NONE;
    }
}

bool ShaderCompiler::Compile( const std::string& path, ShaderStage stage, const std::string& entryPoint, CompiledShader& output)
{
    ENGINE_LOG("ShaderCompiler::Compile() called with path: '{}', stage: {}, entry point: '{}'",
        path, static_cast<int>(stage), entryPoint);
    if( !m_Impl || !m_Impl->Session)
    {
        ENGINE_WARN("ShaderCompiler::Compile m_Impl or m_Impl->Session is Null");
        return false;
    }



    output = {};
    output.Stage = stage;
    output.EntryPoint = entryPoint;

    Slang::ComPtr<slang::IBlob> diagnostics;

    // Load the module from the specified path
    Slang::ComPtr<slang::IModule> module;

    module = m_Impl->Session->loadModule(
        path.c_str(),
        diagnostics.writeRef()
    );

    if (!module)
    {
        const char* msg = diagnostics ? static_cast<const char*>(diagnostics->getBufferPointer()) : "<unknown>";
        ENGINE_ERROR("ShaderCompiler::Compile() failed to load module '{}': {}", path, msg);
        return false;
    }

    // Find the entry point in the module
    Slang::ComPtr<slang::IEntryPoint> entryPointObject;

    SlangResult result = module->findEntryPointByName(
        entryPoint.c_str(),
        entryPointObject.writeRef()
    );

    if (SLANG_FAILED(result))
    {
        ENGINE_ERROR("ShaderCompiler::Compile() failed to find entry point: {}", entryPoint.c_str());
        return false;
    }

    // Get the stage of the entry point and verify it matches the requested stage
    const SlangStage requestedStage = ConvertShaderStage(stage);
    if (requestedStage == SLANG_STAGE_NONE)
    {
        ENGINE_ERROR("ShaderCompiler::Compile() received an invalid shader stage: {}", static_cast<int>(stage));
        return false;
    }

    slang::ProgramLayout* programLayout = entryPointObject->getLayout();
    if (!programLayout || programLayout->getEntryPointCount() == 0)
    {
        ENGINE_ERROR("ShaderCompiler::Compile() failed to reflect entry point: {}", entryPoint.c_str());
        return false;
    }

    slang::EntryPointReflection* entryPointReflection = programLayout->getEntryPointByIndex(0);
    if (!entryPointReflection)
    {
        ENGINE_ERROR("ShaderCompiler::Compile() failed to reflect entry point: {}", entryPoint.c_str());
        return false;
    }

    const SlangStage actualStage = entryPointReflection->getStage();
    if (actualStage != requestedStage)
    {
        ENGINE_ERROR(
            "ShaderCompiler::Compile() stage mismatch for entry point '{}': requested {}, shader declares {}",
            entryPoint,
            ShaderStageToString(stage),
            static_cast<int>(actualStage));
        return false;
    }


    // Create a composite component type that includes the module and the entry point
    std::array<slang::IComponentType*, 2> components = 
    { module, entryPointObject };

    Slang::ComPtr<slang::IComponentType> composedProgram;

    diagnostics = nullptr;

    result = m_Impl->Session->createCompositeComponentType(
        components.data(),
        components.size(),
        composedProgram.writeRef(),
        diagnostics.writeRef()
    );

    if (SLANG_FAILED(result))
    {
        const char* msg = diagnostics ? static_cast<const char*>(diagnostics->getBufferPointer()) : "<unknown>";
        ENGINE_ERROR("ShaderCompiler::Compile() failed to create composite component type: {}", msg);
        return false;
    }

    // Link
    Slang::ComPtr<slang::IComponentType> linkedProgram;

    diagnostics = nullptr;

    result = composedProgram->link(
        linkedProgram.writeRef(),
        diagnostics.writeRef()
    );

    if (SLANG_FAILED(result))
    {
        const char* msg = diagnostics ? static_cast<const char*>(diagnostics->getBufferPointer()) : "<unknown>";
        ENGINE_ERROR("ShaderCompiler::Compile() failed to link program: {}", msg);
        return false;
    }

    // Generate SPIR-V code
    Slang::ComPtr<slang::IBlob> spirvBlob;

    diagnostics = nullptr;

    result = linkedProgram->getEntryPointCode(
        0,
        0,
        spirvBlob.writeRef(),
        diagnostics.writeRef()
    );

    if (SLANG_FAILED(result))
    {
        const char* msg = diagnostics ? static_cast<const char*>(diagnostics->getBufferPointer()) : "<unknown>";
        ENGINE_ERROR("ShaderCompiler::Compile() failed to generate SPIR-V code: {}", msg);
        return false;
    }


    // Copy the SPIR-V code to the output

    const size_t byteSize = spirvBlob->getBufferSize();

    if (byteSize == 0 || byteSize % sizeof(uint32_t) != 0)
    {
        ENGINE_ERROR("ShaderCompiler::Compile() generated SPIR-V code with invalid size: {}", byteSize);
        return false;
    }

    const uint32_t* data = static_cast<const uint32_t*>(spirvBlob->getBufferPointer());

    const size_t wordCount = byteSize / sizeof(uint32_t);

    output.SpirV.assign(
        data,
        data + wordCount
    );

    ENGINE_LOG("ShaderCompiler::Compile() compiled '{}' (stage: {}, entry point: {}) -> {} SPIR-V words",
        path, static_cast<int>(stage), entryPoint, wordCount);

    return true;
}
