#include "Core/Assets/AssetLoader.h"
#include "Core/Assets/ShaderAsset.h"
#include "Core/Filesystem/Filesystem.h"
#include "Core/Log.h"


template<> 
std::shared_ptr<ShaderAsset> AssetLoader<ShaderAsset>::Load(const AssetHandle& handle)
{
    if (handle.Paths.empty())
    {
        ENGINE_ERROR("AssetLoader<ShaderAsset>::Load: No paths provided.");
        return nullptr;
    }

    auto shader = std::make_shared<ShaderAsset>();

    for (const auto& path : handle.Paths)
    {
        ENGINE_LOG("AssetLoader<ShaderAsset>::Load: Loading shader from path: {}", path);
    }
    shader->m_Paths = handle.Paths;

    return shader;
}