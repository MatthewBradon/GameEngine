#include "Core/Log.h"
#include "Core/Assets/AssetRegistry.h"
#include <stdexcept>



ShaderMetadata AssetRegistry::ParseShaderMetadata(const YAML::Node& node)
{
    ShaderMetadata metadata;

    const auto& entryPoints = node["entry_points"];

    if (!entryPoints)
    {
        ENGINE_WARN("Shader asset does not contain 'entry_points' key.");
        return metadata;
    }

    for (const auto& entryPointNode : entryPoints)
    {
        ENGINE_ASSERT(entryPointNode["name"], "Shader entry is missing 'name' key.");
        ENGINE_ASSERT(entryPointNode["stage"], "Shader entry is missing 'stage' key.");

        ShaderEntryPointDesc entryPoint;

        entryPoint.Name = entryPointNode["name"].as<std::string>();
        std::string stageStr = entryPointNode["stage"].as<std::string>();
        
        // Convert stage string to lowercase for case-insensitive comparison
        std::transform(
            stageStr.begin(),
            stageStr.end(),
            stageStr.begin(),
            [](unsigned char c) {
                return static_cast<char>(std::tolower(c));
            }
        );
        
        ENGINE_ASSERT(
            ShaderStageFromString(stageStr, entryPoint.Stage),
            "Unknown shader stage: '{}' for entry point: '{}'", stageStr, entryPoint.Name);

        
        metadata.EntryPoints.push_back(std::move(entryPoint));
    }

    return metadata;
}


AssetMetadata AssetRegistry::ParseMetadata(AssetType type, const YAML::Node& node)
{
    switch (type)
    {
        case AssetType::Shader:
            return ParseShaderMetadata(node);

        default:
            ENGINE_WARN("No metadata parser implemented for asset type: {}", AssetTypeToString(type));
            return std::monostate{};
    }
}

AssetRegistry AssetRegistry::LoadFromYAML(const std::string& yamlFilePath)
{
    AssetRegistry registry;
    ENGINE_LOG("Loading asset registry from YAML file: {}", yamlFilePath);

    YAML::Node root = YAML::LoadFile(yamlFilePath);
    const auto& assets = root["assets"];
    ENGINE_ASSERT(assets, "YAML file does not contain 'assets' key.");
    ENGINE_ASSERT(assets.IsMap(), "'assets' key must be a map.");

    for (const auto& assetNode : assets)
    {
        std::string assetName = assetNode.first.as<std::string>();
        const auto& node = assetNode.second;

        Entry entry;

        // Parse asset type
        ENGINE_ASSERT(node["type"], "Asset '{}' is missing 'type' key.", assetName);

        std::string typeStr = node["type"].as<std::string>();

        std::transform(
            typeStr.begin(),
            typeStr.end(),
            typeStr.begin(),
            [](unsigned char c) {
                return static_cast<char>(std::toupper(c));
            }
        );

        entry.Type = AssetTypeFromString(typeStr);
        
        ENGINE_ASSERT(
            entry.Type != AssetType::None,
            "Unknown asset type: {} for asset: {}", typeStr, assetName
        );


        // Parse paths
        ENGINE_ASSERT(node["paths"], "Asset '{}' is missing 'paths' key.", assetName);

        ENGINE_ASSERT(
            node["paths"].IsSequence(),
            "'paths' key for asset '{}' must be a sequence.", assetName
        );
        
        std::vector<std::string> paths;
        for (const auto& pathNode : node["paths"])
        {
            paths.push_back(pathNode.as<std::string>());
        }

        entry.Handle = AssetHandle(std::move(paths));

        
        // Parse metadata
        entry.Metadata = ParseMetadata(entry.Type, node);



        registry.m_Entries[assetName] = std::move(entry);
    }
    
    return registry;
}