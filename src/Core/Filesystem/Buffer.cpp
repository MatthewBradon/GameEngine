#include "Core/Filesystem/Buffer.h"
#include "Core/Memory/Memory.h"

Buffer::Buffer()
    : m_Data(nullptr), m_Size(0)
{
}

Buffer::Buffer(size_t size)
    : m_Size(size)
{
    m_Data =
        (uint8_t*)Memory::Allocate(size);
}

Buffer::~Buffer()
{
    if (m_Data)
    {
        Memory::Free(m_Data);
        m_Data = nullptr;
    }
}

Buffer::Buffer(Buffer&& other) noexcept
{
    m_Data = other.m_Data;
    m_Size = other.m_Size;

    other.m_Data = nullptr;
    other.m_Size = 0;
}

Buffer& Buffer::operator=(Buffer&& other) noexcept
{
    if (this != &other)
    {
        if (m_Data) 
        {
            Memory::Free(m_Data);
        }

        m_Data = other.m_Data;
        m_Size = other.m_Size;

        other.m_Data = nullptr;
        other.m_Size = 0;
    }

    return *this;
}