#pragma once

#include "Core/Assets/Asset.h"
#include "Core/Assets/AssetType.h"
#include <memory>
#include <string>

enum class TextureFormat
{
    None = 0,
    R8,
    RGB8,
    RGBA8,
    RGBA16F,
    RGBA32F
};

enum class TextureWrapMode
{
    Repeat,
    MirroredRepeat,
    ClampToEdge,
    ClampToBorder
};

enum class TextureFilterMode
{
    Nearest,
    Linear,
    LinearMipmapLinear
};

struct TextureSpecification
{
    uint32_t Width{1};
    uint32_t Height{1};
    TextureFormat Format{TextureFormat::RGBA8};
    TextureWrapMode WrapS{TextureWrapMode::ClampToEdge};
    TextureWrapMode WrapT{TextureWrapMode::ClampToEdge};
    TextureFilterMode MinFilter{TextureFilterMode::Linear};
    TextureFilterMode MagFilter{TextureFilterMode::Linear};
    bool GenerateMipmaps{false};
};

class Texture2D : public Asset
{
public:
    virtual ~Texture2D() = default;

    virtual void Bind(uint32_t slot = 0) const = 0;
    virtual void Unbind() const = 0;

    virtual void SetData(const void* data, uint32_t size) = 0;

    virtual uint32_t GetWidth() const = 0;
    virtual uint32_t GetHeight() const = 0;
    virtual TextureFormat GetFormat() const = 0;
    virtual uint32_t GetRendererID() const = 0;

    virtual bool operator==(const Texture2D& other) const = 0;

    // Create
    static std::shared_ptr<Texture2D> Create(const std::string& path);
    static std::shared_ptr<Texture2D> Create(const TextureSpecification& spec);

    static AssetType GetStaticType() { return AssetType::Texture2D; }
    AssetType GetType() const override { return GetStaticType(); }
};