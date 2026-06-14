#pragma once

#include <cstddef>

constexpr size_t operator"" _KB(unsigned long long x)
{
    return x * 1024ull;
}

constexpr size_t operator"" _MB(unsigned long long x)
{
    return x * 1024ull * 1024ull;
}

constexpr size_t operator"" _GB(unsigned long long x)
{
    return x * 1024ull * 1024ull * 1024ull;
}
