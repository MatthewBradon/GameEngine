#include "Platform/OpenGL/OpenGLTexture2D.h"
#include "Core/Log.h"

#include <stb_image.h>
#include <glad/glad.h>

GLenum OpenGLTexture2D::TextureFormatToOpenGLInternalFormat(TextureFormat format)
{
    switch (format)
    {
        case TextureFormat::RGB8: return GL_RGB8;
        case TextureFormat::RGBA8: return GL_RGBA8;
        case TextureFormat::R8: return GL_R8;
        case TextureFormat::RGBA16F: return GL_RGBA16F;
        case TextureFormat::RGBA32F: return GL_RGBA32F;
        default: ENGINE_ASSERT(false, "Unknown TextureFormat!"); return 0;
    }
}

GLenum OpenGLTexture2D::TextureFormatToOpenGLDataFormat(TextureFormat format)
{
    switch (format)
    {
        case TextureFormat::RGB8: return GL_RGB;
        case TextureFormat::RGBA8: return GL_RGBA;
        case TextureFormat::R8: return GL_RED;
        case TextureFormat::RGBA16F: return GL_RGBA;
        case TextureFormat::RGBA32F: return GL_RGBA;
        default: ENGINE_ASSERT(false, "Unknown TextureFormat!"); return 0;
    }
}

GLenum OpenGLTexture2D::TextureWrapModeToOpenGL(TextureWrapMode wrap)
{
    switch (wrap)
    {
        case TextureWrapMode::Repeat: return GL_REPEAT;
        case TextureWrapMode::MirroredRepeat: return GL_MIRRORED_REPEAT;
        case TextureWrapMode::ClampToEdge: return GL_CLAMP_TO_EDGE;
        case TextureWrapMode::ClampToBorder: return GL_CLAMP_TO_BORDER;
        default: return GL_REPEAT;
    }
}

GLenum OpenGLTexture2D::TextureFilterModeToOpenGL(TextureFilterMode filter)
{
    switch (filter)
    {
        case TextureFilterMode::Nearest: return GL_NEAREST;
        case TextureFilterMode::Linear: return GL_LINEAR;
        case TextureFilterMode::LinearMipmapLinear: return GL_LINEAR_MIPMAP_LINEAR;
        default: return GL_LINEAR;
    }
}


OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
{
    
}