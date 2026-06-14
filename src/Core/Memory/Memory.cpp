#include "Core/Memory/Memory.h"
#include "Core/Memory/TLSFAllocator.h"

static TLSFAllocator* s_Allocator = nullptr;

void Memory::Initialize()
{
    s_Allocator =
        new TLSFAllocator(1024 * 1024 * 128);
}

void* Memory::Allocate(size_t size)
{
    return s_Allocator->Allocate(size);
}

void Memory::Free(void* ptr)
{
    s_Allocator->Free(ptr);
}

void Memory::Shutdown()
{
    delete s_Allocator;
    s_Allocator = nullptr;
}

Memory::~Memory()
{
    if (s_Allocator)
    {
        Shutdown();
    }
}