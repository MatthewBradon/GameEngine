#include "Renderer/BufferLayout.h"

BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements)
    : m_Elements(elements)
{
    CalculateOffsetsAndStride();
}

void BufferLayout::CalculateOffsetsAndStride()
{
    uint32_t offset = 0;
    m_Stride = 0;

    for (auto &element : m_Elements)
    {
        element.Offset = offset;
        offset += element.Size;
        m_Stride += element.Size;
    }
}