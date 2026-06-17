#pragma once
#include "AssetHandle.h"
#include "AssetType.h"

/*
Example YAML

assets.yaml example:
  assets:
    Phong:
      type: Shader
      paths:
        - shaders/phong.vert
        - shaders/phong.frag
    BrickWall:
      type: Texture2D
      paths:
        - textures/brick_albedo.png
    PlayerMesh:
      type: Mesh
      paths:
        - meshes/player.obj
        - meshes/player.mtl

*/

class AssetRegistry
{
public:
    struct Entry
    {
        AssetType Type = AssetType::None;
        AssetHandle Handle;
    };

    static AssetRegistry LoadFromYAML(const std::string& yamlFilePath);

    const Entry* Find(const std::string& assetName) const
    {
        auto it = m_Entries.find(assetName);
        
        return it != m_Entries.end() ? &it->second : nullptr;
    }

    const bool IsEmpty() const
    {
        return m_Entries.empty();
    }

private:
    std::unordered_map<std::string, Entry> m_Entries;

};