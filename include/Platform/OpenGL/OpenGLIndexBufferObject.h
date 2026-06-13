#pragma once

#include "Renderer/IndexBufferObject.h"
#include <cstdint>


class OpenGLIndexBufferObject : public IndexBufferObject
{
public:
    OpenGLIndexBufferObject(uint32_t size);
    OpenGLIndexBufferObject(const void* data, uint32_t size);
    virtual ~OpenGLIndexBufferObject() override;

    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual void SetData(const void* data, uint32_t size) override;

    virtual uint32_t GetCount() const override;

private:
    uint32_t m_RendererID;
    uint32_t m_Count;
};