#pragma once
#include <string_view>

enum class AssetType
{
    None = 0,
    Shader,
    Texture2D,
    Mesh,
    Audio,
    // Add more as needed
};

constexpr std::string_view AssetTypeToString(AssetType type)
{
    switch (type)
    {
        case AssetType::Shader:    return "Shader";
        case AssetType::Texture2D: return "Texture2D";
        case AssetType::Mesh:      return "Mesh";
        case AssetType::Audio:     return "Audio";
        default:                   return "None";
    }
}

constexpr AssetType AssetTypeFromString(std::string_view str)
{
    if (str == "SHADER")    return AssetType::Shader;
    if (str == "TEXTURE2D") return AssetType::Texture2D;
    if (str == "MESH")      return AssetType::Mesh;
    if (str == "AUDIO")     return AssetType::Audio;
    return AssetType::None;
}