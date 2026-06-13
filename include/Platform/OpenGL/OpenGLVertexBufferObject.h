#include "Renderer/VertexBufferObject.h"
#include "Renderer/BufferLayout.h"

class OpenGLVertexBufferObject : public VertexBufferObject
{
public:
    OpenGLVertexBufferObject(uint32_t size);
    OpenGLVertexBufferObject(const void* data, uint32_t size);

    virtual ~OpenGLVertexBufferObject() override;

    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual void SetData(const void* data, uint32_t size) override;

    virtual void SetLayout(const class BufferLayout& layout) override;
    virtual const class BufferLayout& GetLayout() const override;

private:
    unsigned int m_RendererID;
    unsigned int m_Size;
    BufferLayout m_Layout;
};