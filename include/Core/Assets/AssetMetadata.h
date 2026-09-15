#pragma once

#include "Renderer/Shader/ShaderStage.h"

#include <string>
#include <variant>
#include <vector>

struct ShaderEntryPointDesc
{
    std::string Name;
    ShaderStage Stage;
};

struct ShaderMetadata
{
    std::vector<ShaderEntryPointDesc> EntryPoints;
};

using AssetMetadata = std::variant<
    std::monostate,
    ShaderMetadata
>;




// struct TextureMetadata
// {
//     bool GenerateMipmaps = true;
// };

// struct MeshMetadata
// {
//     bool GenerateTangents = true;
// };