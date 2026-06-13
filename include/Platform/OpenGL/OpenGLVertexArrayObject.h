#pragma once

#include "Renderer/VertexArrayObject.h"

#include <vector>

class OpenGLVertexArrayObject : public VertexArrayObject
{
public:
    OpenGLVertexArrayObject();

    virtual ~OpenGLVertexArrayObject() override;

    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual void AddVertexBuffer(
        const std::shared_ptr<VertexBufferObject>& VBO) override;

    virtual void SetIndexBuffer(
        const std::shared_ptr<IndexBufferObject>& IBO) override;

    virtual const std::shared_ptr<IndexBufferObject>& GetIndexBuffer() const override;

private:
    unsigned int m_RendererID;
    std::vector<std::shared_ptr<VertexBufferObject>> m_VertexBuffers;
    std::shared_ptr<IndexBufferObject> m_IndexBuffer;
};