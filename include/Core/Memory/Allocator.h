#pragma once

#include <cstddef>

class Allocator
{
public:
    virtual ~Allocator() = default;

    virtual void* Allocate(size_t size) = 0;

    virtual void Free(void* ptr) = 0;
};