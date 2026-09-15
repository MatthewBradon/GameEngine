#pragma once
#include "AssetHandle.h"
#include "AssetType.h"
#include "AssetMetadata.h"
#include <yaml-cpp/yaml.h>


#include <variant>
/*
Example YAML
assets:
    Phong:
      type: Shader
      paths:
        - shaders/phong.slang

      entry_points:
        - name: main
          stage: vertex

        - name: main
          stage: fragment

  Bloom:
    type: Shader
    paths:
      - shaders/bloom.slang

    entry_points:
      - name: main
        stage: compute

*/

class AssetRegistry
{
public:
    struct Entry
    {
        AssetType Type = AssetType::None;
        AssetHandle Handle;
        AssetMetadata Metadata;
        
    };

    static AssetRegistry LoadFromYAML(const std::string& yamlFilePath);

    const Entry* Find(const std::string& assetName) const
    {
        auto it = m_Entries.find(assetName);
        
        return it != m_Entries.end() ? &it->second : nullptr;
    }

    bool IsEmpty() const { return m_Entries.empty(); }

private:
    static AssetMetadata ParseMetadata(AssetType type, const YAML::Node& node);
    static ShaderMetadata ParseShaderMetadata(const YAML::Node& node);
    std::unordered_map<std::string, Entry> m_Entries;

};