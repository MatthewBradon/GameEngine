#pragma once
#include "AssetHandle.h"
#include "AssetType.h"
#include <string>

enum class AssetStatus
{
    Unloaded,
    Loading,
    Ready,
    Failed
};

class Asset
{
public:
    virtual ~Asset() = default;

    virtual AssetType GetType() const = 0;

    const AssetHandle& GetHandle() const { return m_Handle; }
    AssetStatus GetStatus() const { return m_Status; }

    const std::string& GetPath() const
    {
        static const std::string emptyString;
        return m_Handle.Paths.empty() ? emptyString : m_Handle.Paths[0];
    }

protected:
    AssetHandle m_Handle;
    AssetStatus m_Status;

    friend class AssetManager;
};