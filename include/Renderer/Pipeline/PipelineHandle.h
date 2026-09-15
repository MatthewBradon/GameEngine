#pragma once

#include <cstdint>
#include <limits>

struct PipelineHandle
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

    bool operator==(const PipelineHandle& other) const
    {
        return Index == other.Index;
    }

    bool operator!=(const PipelineHandle& other) const
    {
        return !(*this == other);
    }
};