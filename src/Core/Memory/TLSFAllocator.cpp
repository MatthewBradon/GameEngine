#include "Core/Memory/TLSFAllocator.h"

#include "tlsf/tlsf.h"

#include <cstdlib>

TLSFAllocator::TLSFAllocator(size_t poolSize)
{
    m_PoolMemory = malloc(poolSize);

    m_TLSFHandle =
        tlsf_create_with_pool(
            m_PoolMemory,
            poolSize);
}

void* TLSFAllocator::Allocate(size_t size)
{
    return tlsf_malloc(m_TLSFHandle, size);
}

void TLSFAllocator::Free(void* ptr)
{
    tlsf_free(m_TLSFHandle, ptr);
}

TLSFAllocator::~TLSFAllocator()
{
    tlsf_destroy(m_TLSFHandle);

    free(m_PoolMemory);
}

