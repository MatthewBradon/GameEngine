#pragma once

#include "Core/Assets/Asset.h"

#include <string>
#include <memory>
#include <glm/glm.hpp>

class Shader : public Asset
{
public:
    virtual ~Shader() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
    
    static std::shared_ptr<Shader> Create(const std::string& vertexSrc, const std::string& fragmentSrc);
    static std::shared_ptr<Shader> Create(const std::string& vertexSrc, const std::string& geometrySrc, const std::string& fragmentSrc);

    virtual void SetInt(const std::string& name, int value) = 0;
    virtual void SetFloat(const std::string& name, float value) = 0;
    virtual void SetBool(const std::string& name, bool value) = 0;

    virtual void SetMat2(const std::string& name, const glm::mat2& matrix) = 0;
    virtual void SetMat3(const std::string& name, const glm::mat3& matrix) = 0;
    virtual void SetMat4(const std::string& name, const glm::mat4& matrix) = 0;
    virtual void SetVec3(const std::string& name, const glm::vec3& vector) = 0;
    virtual void SetVec4(const std::string& name, const glm::vec4& vector) = 0;
    virtual void SetVec3(const std::string& name, float x, float y, float z) = 0;
    virtual void SetVec4(const std::string& name, float x, float y, float z, float w) = 0;
    
};