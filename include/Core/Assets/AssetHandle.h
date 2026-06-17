#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

struct AssetHandle
{
    std::vector<std::string> Paths;
    
    AssetHandle() = default;

    explicit AssetHandle(std::initializer_list<std::string> paths)
        : Paths(paths)
    {
        std::sort(Paths.begin(), Paths.end());
    }

    explicit AssetHandle(std::vector<std::string> paths)
        : Paths(std::move(paths))
    {
        std::sort(Paths.begin(), Paths.end());
    }

    static AssetHandle Create(const std::string& path)
    {
        return AssetHandle({ path });
    }

    bool operator==(const AssetHandle& other) const
    {
        return Paths == other.Paths;
    }

    bool IsValid() const
    {
        return !Paths.empty();
    }

    std::string ToString() const
    {
        std::string result;
        for (const auto& path : Paths)
        {
            result += path + ";";
        }
        return result;
    }


};

struct AssetHandleHash
{
    std::size_t operator()(const AssetHandle& handle) const
    {
        std::size_t seed = 0;
        std::hash<std::string> hasher;
        for (const auto& path : handle.Paths)
        {
            // Combine the hash of the current path with the seed
            seed ^= hasher(path) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};