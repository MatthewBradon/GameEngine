#pragma once

#include "Allocator.h"

class TLSFAllocator : public Allocator
{
public:
    TLSFAllocator(size_t poolSize);

    ~TLSFAllocator();

    void* Allocate(size_t size) override;

    void Free(void* ptr) override;

private:
    void* m_PoolMemory;
    void* m_TLSFHandle;
};