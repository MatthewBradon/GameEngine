#include "Core/Log.h"
#include "Core/Assets/AssetRegistry.h"
#include <yaml-cpp/yaml.h>
#include <stdexcept>

AssetRegistry AssetRegistry::LoadFromYAML(const std::string& yamlFilePath)
{
    AssetRegistry registry;

    YAML::Node root = YAML::LoadFile(yamlFilePath);
    const auto& assets = root["assets"];

    ENGINE_ASSERT(assets, "YAML file does not contain 'assets' key.");
    ENGINE_ASSERT(assets.IsMap(), "'assets' key must be a map.");

    for (const auto& assetNode : assets)
    {
        std::string assetName = assetNode.first.as<std::string>();
        const auto& node = assetNode.second;

        Entry entry;
        std::string typeStr = node["type"].as<std::string>();
        std::transform(typeStr.begin(), typeStr.end(), typeStr.begin(), ::toupper);
        entry.Type = AssetTypeFromString(typeStr);
        
        ENGINE_ASSERT(entry.Type != AssetType::None, "Unknown asset type: {}", typeStr);

        std::vector<std::string> paths;
        for (const auto& pathNode : node["paths"])
        {
            paths.push_back(pathNode.as<std::string>());
        }

        entry.Handle = AssetHandle(std::move(paths));
        registry.m_Entries[assetName] = std::move(entry);
    }
    
    return registry;
}