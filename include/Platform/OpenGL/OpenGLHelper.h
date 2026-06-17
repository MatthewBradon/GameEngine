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

static uint32_t ShaderDataTypeComponentCount(ShaderDataType type)
{
    switch (type)
    {
        case ShaderDataType::Float:  return 1;
        case ShaderDataType::Float2: return 2;
        case ShaderDataType::Float3: return 3;
        case ShaderDataType::Float4: return 4;
        case ShaderDataType::Int:    return 1;
        case ShaderDataType::Int2:   return 2;
        case ShaderDataType::Int3:   return 3;
        case ShaderDataType::Int4:   return 4;
    }
    return 0;
}