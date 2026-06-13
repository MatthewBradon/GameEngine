#include "Renderer/Shader.h"

class OpenGLShader : public Shader {
public:
    OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
    OpenGLShader(const std::string& vertexSrc, const std::string& geometrySrc, const std::string& fragmentSrc);

    virtual ~OpenGLShader() override;

    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual void SetInt(const std::string& name, int value) override;
    virtual void SetFloat(const std::string& name, float value) override;
    virtual void SetBool(const std::string& name, bool value) override;
    virtual void SetMat2(const std::string& name, const glm::mat2& matrix) override;
    virtual void SetMat3(const std::string& name, const glm::mat3& matrix) override;
    virtual void SetMat4(const std::string& name, const glm::mat4& matrix) override;
    virtual void SetVec3(const std::string& name, const glm::vec3& vector) override;
    virtual void SetVec4(const std::string& name, const glm::vec4& vector) override;
    virtual void SetVec3(const std::string& name, float x, float y, float z) override;
    virtual void SetVec4(const std::string& name, float x, float y, float z, float w) override;


private:
    unsigned int m_RendererID;
};