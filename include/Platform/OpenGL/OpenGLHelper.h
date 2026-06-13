#pragma once

#include "Renderer/BufferLayout.h"

#include <glad/glad.h>
#include <unordered_map>


static std::unordered_map<ShaderDataType, GLenum> ShaderDataTypeToOpenGLBaseTypeMap = {
    { ShaderDataType::Float,  GL_FLOAT },
    { ShaderDataType::Float2, GL_FLOAT },
    { ShaderDataType::Float3, GL_FLOAT },
    { ShaderDataType::Float4, GL_FLOAT },

    { ShaderDataType::Int,  GL_INT },
    { ShaderDataType::Int2, GL_INT },
    { ShaderDataType::Int3, GL_INT },
    { ShaderDataType::Int4, GL_INT }
};

static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
{
    auto it = ShaderDataTypeToOpenGLBaseTypeMap.find(type);
    
    if (it != ShaderDataTypeToOpenGLBaseTypeMap.end()) {
        return it->second;
    }
    return GL_NONE; 
}