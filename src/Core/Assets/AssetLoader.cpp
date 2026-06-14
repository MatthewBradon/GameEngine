#include "Core/Assets/AssetLoader.h"
#include "Core/Filesystem/Filesystem.h"
#include "Renderer/Shader.h"

std::shared_ptr<Shader> AssetLoader<Shader>::Load(const std::string& vertexPath, const std::string& fragmentPath)
{
    std::string vertexSource = FileSystem::ReadText(vertexPath);
    std::string fragmentSource = FileSystem::ReadText(fragmentPath);

    return Shader::Create(vertexSource, fragmentSource);
}

std::shared_ptr<Shader> AssetLoader<Shader>::Load(const std::string& vertexPath, const std::string& geometryPath, const std::string& fragmentPath)
{
    std::string vertexSource = FileSystem::ReadText(vertexPath);
    std::string geometrySource = FileSystem::ReadText(geometryPath);
    std::string fragmentSource = FileSystem::ReadText(fragmentPath);

    return Shader::Create(vertexSource, geometrySource, fragmentSource);
}