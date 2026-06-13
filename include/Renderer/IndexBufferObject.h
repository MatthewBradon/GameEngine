#pragma once


#include <cstdint>
#include <memory>

class IndexBufferObject
{
public:
    virtual ~IndexBufferObject() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual void SetData(const void* data, uint32_t size) = 0;

    virtual uint32_t GetCount() const = 0;

    static std::shared_ptr<IndexBufferObject> Create(uint32_t size);
    static std::shared_ptr<IndexBufferObject> Create(uint32_t* data, uint32_t size);
};