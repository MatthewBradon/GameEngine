#include "Renderer/VertexBufferObject.h"

#include "Platform/OpenGL/OpenGLVertexBufferObject.h"

std::shared_ptr<VertexBufferObject> VertexBufferObject::Create(uint32_t size)
{
    return std::shared_ptr<VertexBufferObject>(new OpenGLVertexBufferObject(size));
}

std::shared_ptr<VertexBufferObject> VertexBufferObject::Create(const void* data, uint32_t size)
{
    return std::shared_ptr<VertexBufferObject>(new OpenGLVertexBufferObject(data, size));
}