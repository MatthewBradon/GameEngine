#pragma once

#include <memory>
#include <string>

template<typename T>
class AssetLoader
{
public:
    static std::shared_ptr<T> Load(const std::string& path);
    static std::shared_ptr<Shader> Load(const std::string& vertexPath, const std::string& fragmentPath);
    static std::shared_ptr<Shader> Load(const std::string& vertexPath, const std::string& geometryPath, const std::string& fragmentPath);
};