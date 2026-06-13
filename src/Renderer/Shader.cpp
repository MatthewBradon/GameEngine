#include "Renderer/Shader.h"

#include "Platform/OpenGL/OpenGLShader.h"

std::unique_ptr<Shader> Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
{
    return std::unique_ptr<Shader>(new OpenGLShader(vertexSrc, fragmentSrc));
}

std::unique_ptr<Shader> Shader::Create(const std::string& vertexSrc, const std::string& geometrySrc, const std::string& fragmentSrc)
{
    return std::unique_ptr<Shader>(new OpenGLShader(vertexSrc, geometrySrc, fragmentSrc));
}