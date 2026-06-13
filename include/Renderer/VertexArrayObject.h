#pragma once

#include <memory>

class VertexBufferObject;
class IndexBufferObject;

class VertexArrayObject
{
public:
    virtual ~VertexArrayObject() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual void AddVertexBuffer(
        const std::shared_ptr<VertexBufferObject>& VBO) = 0;

    virtual void SetIndexBuffer(
        const std::shared_ptr<IndexBufferObject>& IBO) = 0;

    virtual const std::shared_ptr<IndexBufferObject>& GetIndexBuffer() const = 0;

    static VertexArrayObject* Create();
};