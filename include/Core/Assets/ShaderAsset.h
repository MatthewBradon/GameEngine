#pragma once

#include "Asset.h"
#include "Renderer/Shader/ShaderStage.h"
#include "AssetMetadata.h"

#include <string>
#include <vector>

/*
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



template<typename T>
class AssetLoader;

class ShaderAsset : public Asset
{
public:

    static constexpr AssetType GetStaticType()
    {
        return AssetType::Shader;
    }

    AssetType GetType() const override
    {
        return GetStaticType();
    }

    const std::vector<std::string>& GetPaths() const
    {
        return m_Paths;
    }

    const std::string& GetSourcePath() const
    {
        return m_Paths[0];
    }

    const std::vector<ShaderEntryPointDesc>& GetEntryPoints() const
    {
        return m_EntryPoints;
    }


    void Configure(const AssetMetadata& metadata) override
    {
        const auto* shaderMetadata = std::get_if<ShaderMetadata>(&metadata);

        if (!shaderMetadata) return;

        m_EntryPoints = shaderMetadata->EntryPoints;
    }

private:

    std::vector<std::string> m_Paths;

    std::vector<ShaderEntryPointDesc> m_EntryPoints;

    friend class AssetLoader<ShaderAsset>;
};