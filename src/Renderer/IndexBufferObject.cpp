#include "Renderer/IndexBufferObject.h"

#include "Platform/OpenGL/OpenGLIndexBufferObject.h"

std::shared_ptr<IndexBufferObject> IndexBufferObject::Create(uint32_t* data, uint32_t size)
{
    return std::shared_ptr<IndexBufferObject>(new OpenGLIndexBufferObject(data, size));
}

std::shared_ptr<IndexBufferObject> IndexBufferObject::Create(uint32_t size)
{
    return std::shared_ptr<IndexBufferObject>(new OpenGLIndexBufferObject(size));
}