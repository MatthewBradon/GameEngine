#include "Renderer/VertexArrayObject.h"

#include "Platform/OpenGL/OpenGLVertexArrayObject.h"

std::shared_ptr<VertexArrayObject> VertexArrayObject::Create()
{
    return std::shared_ptr<VertexArrayObject>(new OpenGLVertexArrayObject());
}
