#include "Platform/OpenGL/OpenGLIndexBufferObject.h"

#include <glad/glad.h>

OpenGLIndexBufferObject::OpenGLIndexBufferObject(uint32_t size)
{
    m_Count = size / sizeof(uint32_t);

    glCreateBuffers(1, &m_RendererID);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

OpenGLIndexBufferObject::OpenGLIndexBufferObject(const void* data, uint32_t size)
{
    m_Count = size / sizeof(uint32_t);

    glCreateBuffers(1, &m_RendererID);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

OpenGLIndexBufferObject::~OpenGLIndexBufferObject()
{
    glDeleteBuffers(1, &m_RendererID);
}

void OpenGLIndexBufferObject::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void OpenGLIndexBufferObject::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void OpenGLIndexBufferObject::SetData(const void* data, uint32_t size)
{
    m_Count = size / sizeof(uint32_t);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);

    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, data);
}

uint32_t OpenGLIndexBufferObject::GetCount() const
{
    return m_Count;
}