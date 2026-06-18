#pragma once

#include "Renderer/Texture2D.h"
#include <glad/glad.h>

class OpenGLTexture2D : public Texture2D
{
public:
    OpenGLTexture2D(const std::string& path);
    OpenGLTexture2D(const TextureSpecification& spec);
    virtual ~OpenGLTexture2D() override;

    void Bind(uint32_t slot = 0) const override;
    void Unbind() const override;

    void SetData(const void* data, uint32_t size) override;

    uint32_t GetWidth() const override { return m_Width; }
    uint32_t GetHeight() const override { return m_Height; }
    TextureFormat GetFormat() const override { return m_Format; }
    uint32_t GetRendererID() const override { return m_RendererID; }

    bool operator==(const Texture2D& other) const override
    {
        return m_RendererID == static_cast<const OpenGLTexture2D&>(other).m_RendererID;
    }

private:

    static GLenum TextureFormatToOpenGLInternalFormat(TextureFormat format);
    static GLenum TextureFormatToOpenGLDataFormat(TextureFormat format);
    static GLenum TextureWrapModeToOpenGL(TextureWrapMode wrapMode);
    static GLenum TextureFilterModeToOpenGL(TextureFilterMode filterMode);


    uint32_t m_RendererID{0};
    uint32_t m_Width{0};
    uint32_t m_Height{0};
    TextureFormat m_Format{};
};