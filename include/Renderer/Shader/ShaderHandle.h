#pragma once

#include <cstdint>
#include <limits>

struct ShaderHandle
{
    static constexpr uint32_t InvalidIndex = std::numeric_limits<uint32_t>::max();

    uint32_t Index = InvalidIndex;

    bool IsValid() const
    {
        return Index != InvalidIndex;
    }

    explicit operator bool() const
    {
        return IsValid();
    }

    bool operator==(const ShaderHandle& other) const
    {
        return Index == other.Index;
    }

    bool operator!=(const ShaderHandle& other) const
    {
        return !(*this == other);
    }
};