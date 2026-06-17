#include "Core/Assets/AssetLoader.h"
#include "Renderer/Shader.h"
#include "Core/Filesystem/Filesystem.h"
#include "Core/Log.h"

template<>
std::shared_ptr<Shader> AssetLoader<Shader>::Load(const AssetHandle& handle)
{
    if (!handle.IsValid())
    {
        ENGINE_ERROR("AssetLoader<Shader>::Load: Invalid handle provided.");
        return nullptr;
    }

    std::string vertexSrc, fragmentSrc, geometrySrc;

    for (const auto& path : handle.Paths)
    {
        std::string extension = FileSystem::GetFileExtension(path);
        if (extension == ".vert")
            vertexSrc = FileSystem::ReadText(path);
        else if (extension == ".frag")
            fragmentSrc = FileSystem::ReadText(path);
        else if (extension == ".geom")
            geometrySrc = FileSystem::ReadText(path);
    }

    if (vertexSrc.empty() || fragmentSrc.empty())
    {
        ENGINE_ERROR("AssetLoader<Shader>::Load: Missing vertex or fragment shader source.");
        return nullptr;
    }

    if (!geometrySrc.empty())
    {
        return Shader::Create(vertexSrc, geometrySrc, fragmentSrc);
    }
    
    return Shader::Create(vertexSrc, fragmentSrc);
}
