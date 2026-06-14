#pragma once


#include <memory>
#include <unordered_map>
#include <string>

#include "Core/Assets/AssetLoader.h"
#include "Core/Filesystem/Filesystem.h"
#include "Renderer/Shader.h"

class Asset;

class AssetManager
{
public:
    template<typename T>
    static std::shared_ptr<T> Load(const std::string& path);
    
    static std::shared_ptr<Shader> Load(const std::string& vertexPath, const std::string& fragmentPath);
    static std::shared_ptr<Shader> Load(const std::string& vertexPath, const std::string& geometryPath, const std::string& fragmentPath);

    static void Initialize();

    static void Shutdown();

private:
    inline static std::unordered_map<
        std::string,
        std::shared_ptr<Asset>> s_AssetCache;
};



template<typename T>
std::shared_ptr<T> AssetManager::Load(const std::string& path)
{
    auto it = s_AssetCache.find(path);
    if (it != s_AssetCache.end())
        return std::static_pointer_cast<T>(it->second);

    std::shared_ptr<T> asset = AssetLoader<T>::Load(path);

    s_AssetCache[path] = asset;

    return asset;
}

std::shared_ptr<Shader> AssetManager::Load(const std::string& vertexPath, const std::string& fragmentPath)
{
    std::string key = vertexPath + "|" + fragmentPath;

    auto it = s_AssetCache.find(key);
    if (it != s_AssetCache.end())
        return std::static_pointer_cast<Shader>(it->second);

    std::shared_ptr<Shader> shader = AssetLoader<Shader>::Load(vertexPath, fragmentPath);

    s_AssetCache[key] = shader;

    return shader;
}

std::shared_ptr<Shader> AssetManager::Load(const std::string& vertexPath, const std::string& geometryPath, const std::string& fragmentPath)
{
    std::string key = vertexPath + "|" + geometryPath + "|" + fragmentPath;

    auto it = s_AssetCache.find(key);
    if (it != s_AssetCache.end())
        return std::static_pointer_cast<Shader>(it->second);

    std::shared_ptr<Shader> shader = AssetLoader<Shader>::Load(vertexPath, geometryPath, fragmentPath);

    s_AssetCache[key] = shader;

    return shader;
}