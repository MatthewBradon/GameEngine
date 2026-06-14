#include "Renderer/Shader.h"

#include "Platform/OpenGL/OpenGLShader.h"

std::shared_ptr<Shader> Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
{
    return std::make_shared<OpenGLShader>(vertexSrc, fragmentSrc);
}

std::shared_ptr<Shader> Shader::Create(const std::string& vertexSrc, const std::string& geometrySrc, const std::string& fragmentSrc)
{
    return std::make_shared<OpenGLShader>(vertexSrc, geometrySrc, fragmentSrc);
}