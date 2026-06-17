#pragma once
#include "AssetHandle.h"
#include "AssetLoader.h"
#include "AssetType.h"
#include "AssetRegistry.h"
#include "Asset.h"
#include "Core/Log.h"


#include <memory>
#include <unordered_map>
#include <string>

class AssetManager
{
public:

    static void Initalize(const std::string& registryPath="assets/assets.yaml");
    static void Shutdown();

    // Load raw handle
    template<typename T>
    static std::shared_ptr<T> Load(const AssetHandle& handle);

    template<typename T>
    static std::shared_ptr<T> Load(const std::string& path)
    {
        return Load<T>(AssetHandle::Create(path));
    }

    template<typename T>
    static std::shared_ptr<T> Load( const std::initializer_list<std::string>& paths)
    {
        return Load<T>(AssetHandle(paths));
    }

    template<typename T>
    static std::shared_ptr<T> Get(const std::string& name);


    static void Evict(const AssetHandle& handle);
    static void EvictAll();

    // Removes expired weak_ptrs without unloading live assets
    static void PurgeExpired();

    static const AssetRegistry& GetRegistry() { return s_Registry; }

private:
    inline static AssetRegistry s_Registry;
    
    inline static std::unordered_map<
        AssetHandle,
        std::weak_ptr<Asset>, 
        AssetHandleHash> s_AssetCache;

};

template<typename T>
std::shared_ptr<T> AssetManager::Load(const AssetHandle& handle)
{
    // Check cache
    auto it = s_AssetCache.find(handle);
    if (it != s_AssetCache.end())
    {
        auto assetPtr = it->second.lock();
        
        if (assetPtr)
        {
            ENGINE_TRACE("Asset with handle {} found in cache.", handle.ToString());
            return std::static_pointer_cast<T>(assetPtr);
        }
    }

    
    std::shared_ptr<T> asset = AssetLoader<T>::Load(handle);
    
    if (!asset)
    {
        ENGINE_ERROR("Failed to load asset with handle: {}", handle.ToString());
        return nullptr;
    }


    asset->m_Handle = handle;
    asset->m_Status = AssetStatus::Ready;
    s_AssetCache[handle] = std::static_pointer_cast<Asset>(asset);

    return asset;
}

template<typename T>
std::shared_ptr<T> AssetManager::Get(const std::string& name)
{
    const AssetRegistry::Entry* entry = s_Registry.Find(name);
    if (!entry)
    {
        ENGINE_ERROR("Asset with name '{}' not found in registry.", name);
        return nullptr;
    }

    if (entry->Type != T::GetStaticType())
    {
        ENGINE_ERROR("Asset type mismatch for '{}'. Expected: {}, Found: {}", name, AssetTypeToString(T::GetStaticType()), AssetTypeToString(entry->Type));
        return nullptr;
    }

    return Load<T>(entry->Handle);
}