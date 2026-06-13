#pragma once

#include <cstdint>
#include <memory>

class BufferLayout;

class VertexBufferObject
{
    public:
        virtual ~VertexBufferObject() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetData(const void* data, uint32_t size) = 0;

        virtual void SetLayout(const class BufferLayout& layout) = 0;
        virtual const class BufferLayout& GetLayout() const = 0;

        static std::shared_ptr<VertexBufferObject> Create(uint32_t size);
        static std::shared_ptr<VertexBufferObject> Create(const void* data, uint32_t size);
};