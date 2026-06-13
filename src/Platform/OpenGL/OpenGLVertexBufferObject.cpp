#include "Platform/OpenGL/OpenGLVertexBufferObject.h"

#include <glad/glad.h>

OpenGLVertexBufferObject::OpenGLVertexBufferObject(uint32_t size)
    : m_Size(size)
{
    glCreateBuffers(1, &m_RendererID);

    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);

    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

OpenGLVertexBufferObject::OpenGLVertexBufferObject(const void* data, uint32_t size)
    : m_Size(size)
{
    glCreateBuffers(1, &m_RendererID);

    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);

    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

OpenGLVertexBufferObject::~OpenGLVertexBufferObject()
{
    glDeleteBuffers(1, &m_RendererID);
}

void OpenGLVertexBufferObject::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void OpenGLVertexBufferObject::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLVertexBufferObject::SetData(const void* data, uint32_t size)
{
    m_Size = size;

    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);

    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

void OpenGLVertexBufferObject::SetLayout(const BufferLayout& layout)
{
    m_Layout = layout;
}

const BufferLayout& OpenGLVertexBufferObject::GetLayout() const
{
    return m_Layout;
}