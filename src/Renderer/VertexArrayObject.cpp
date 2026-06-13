#include "Renderer/VertexArrayObject.h"

#include "Platform/OpenGL/OpenGLVertexArrayObject.h"

VertexArrayObject* VertexArrayObject::Create()
{
    return new OpenGLVertexArrayObject();
}
