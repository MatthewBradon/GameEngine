#pragma once

#include <cstddef>

class Memory
{
public:
    static void Initialize();

    static void Shutdown();

    static void* Allocate(size_t size);

    static void Free(void* ptr);

    ~Memory();
};