#pragma once

#include <cstddef>
#include <cstdint>

class Buffer
{
public:
    Buffer();

    Buffer(size_t size);

    ~Buffer();

    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;

    Buffer(Buffer&& other) noexcept;
    Buffer& operator=(Buffer&& other) noexcept;

    uint8_t* Data();

    const uint8_t* Data() const;

    size_t Size() const;

    bool IsValid() const;

private:
    uint8_t* m_Data;
    size_t m_Size;
};