#include "Platform/OpenGL/OpenGLShader.h"
#include "Core/Log.h"

#include <glad/glad.h>


std::unordered_map<int, std::string> ShaderTypeToString = {
    {GL_VERTEX_SHADER, "VERTEX"},
    {GL_FRAGMENT_SHADER, "FRAGMENT"},
    {GL_GEOMETRY_SHADER, "GEOMETRY"}
};

static void CheckCompileErrors(unsigned int shader, const std::string& type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            ENGINE_ERROR("Shader compilation error of type: {}\n{}", type, infoLog);
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            ENGINE_ERROR("Program linking error of type: {}\n{}", type, infoLog);
        }
    }
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    CheckCompileErrors(shader, ShaderTypeToString[type]);

    return shader;
}

static unsigned int LinkProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    CheckCompileErrors(program, "PROGRAM");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

static unsigned int LinkProgram(unsigned int vertexShader, unsigned int geometryShader, unsigned int fragmentShader)
{
    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, geometryShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    CheckCompileErrors(program, "PROGRAM");

    glDeleteShader(vertexShader);
    glDeleteShader(geometryShader);
    glDeleteShader(fragmentShader);

    return program;
}

OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
{
    unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSrc);
    unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSrc);
    m_RendererID = LinkProgram(vertexShader, fragmentShader);
}

OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& geometrySrc, const std::string& fragmentSrc)
{
    unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSrc);
    unsigned int geometryShader = CompileShader(GL_GEOMETRY_SHADER, geometrySrc);
    unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSrc);
    m_RendererID = LinkProgram(vertexShader, geometryShader, fragmentShader);
}


OpenGLShader::~OpenGLShader()
{
    glDeleteProgram(m_RendererID);
}

void OpenGLShader::Bind() const
{
    glUseProgram(m_RendererID);
}

void OpenGLShader::Unbind() const
{
    glUseProgram(0);
}

void OpenGLShader::SetInt(const std::string& name, int value)
{
    glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), value);
}

void OpenGLShader::SetFloat(const std::string& name, float value)
{
    glUniform1f(glGetUniformLocation(m_RendererID, name.c_str()), value);
}

void OpenGLShader::SetBool(const std::string& name, bool value)
{
    glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), value);
}

void OpenGLShader::SetMat2(const std::string& name, const glm::mat2& matrix)
{
    glUniformMatrix2fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
}

void OpenGLShader::SetMat3(const std::string& name, const glm::mat3& matrix)
{
    glUniformMatrix3fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
}

void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
}

void OpenGLShader::SetVec3(const std::string& name, const glm::vec3& vector)
{
    glUniform3f(glGetUniformLocation(m_RendererID, name.c_str()), vector.x, vector.y, vector.z);
}

void OpenGLShader::SetVec4(const std::string& name, const glm::vec4& vector)
{
    glUniform4f(glGetUniformLocation(m_RendererID, name.c_str()), vector.x, vector.y, vector.z, vector.w);
}

void OpenGLShader::SetVec3(const std::string& name, float x, float y, float z)
{
    glUniform3f(glGetUniformLocation(m_RendererID, name.c_str()), x, y, z);
}

void OpenGLShader::SetVec4(const std::string& name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(m_RendererID, name.c_str()), x, y, z, w);
}