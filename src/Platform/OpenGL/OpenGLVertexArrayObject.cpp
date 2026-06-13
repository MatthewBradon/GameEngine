#include "Platform/OpenGL/OpenGLVertexArrayObject.h"

#include "Renderer/VertexBufferObject.h"
#include "Renderer/IndexBufferObject.h"
#include "Renderer/BufferLayout.h"
#include "Platform/OpenGL/OpenGLHelper.h"

#include <glad/glad.h>
#include <unordered_map>



OpenGLVertexArrayObject::OpenGLVertexArrayObject()
{
    glCreateVertexArrays(1, &m_RendererID);
}

OpenGLVertexArrayObject::~OpenGLVertexArrayObject()
{
    glDeleteVertexArrays(1, &m_RendererID);
}

void OpenGLVertexArrayObject::Bind() const
{
    glBindVertexArray(m_RendererID);
}

void OpenGLVertexArrayObject::Unbind() const
{
    glBindVertexArray(0);
}

void OpenGLVertexArrayObject::AddVertexBuffer(
    const std::shared_ptr<VertexBufferObject>& VBO)
{
    Bind();

    VBO->Bind();

    const BufferLayout& layout = VBO->GetLayout();

    uint32_t index{0};

    for (const auto& element: layout.GetElements())
    {
        glEnableVertexAttribArray(index);

        glVertexAttribPointer(
            index,
            ShaderDataTypeSize(element.Type),
            ShaderDataTypeToOpenGLBaseType(element.Type),
            element.Normalized ? GL_TRUE : GL_FALSE,
            layout.GetStride(),
            (const void*)(uintptr_t)(element.Offset)
        );

        index++;
    }

    m_VertexBuffers.push_back(VBO);
}

void OpenGLVertexArrayObject::SetIndexBuffer(
    const std::shared_ptr<IndexBufferObject>& IBO)
{
    Bind();

    IBO->Bind();

    m_IndexBuffer = IBO;
}

const std::shared_ptr<IndexBufferObject>& OpenGLVertexArrayObject::GetIndexBuffer() const
{
    return m_IndexBuffer;
}

