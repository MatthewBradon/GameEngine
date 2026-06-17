#include "Core/Assets/AssetManager.h"
#include <algorithm>

void AssetManager::Initalize(const std::string& registryPath)
{
    if (registryPath.empty())
    {
        ENGINE_ERROR("AssetManager::Initalize: Registry path is empty.");    
        return;
    }

    s_Registry = AssetRegistry::LoadFromYAML(registryPath);

}

void AssetManager::Shutdown()
{
    s_AssetCache.clear();
}

void AssetManager::Evict(const AssetHandle& handle)
{
    if(s_AssetCache.erase(handle) == 0)
    {
        ENGINE_WARN("AssetManager::Evict: Asset not found in cache: {}", handle.ToString());
    }
    else
    {
        ENGINE_TRACE("AssetManager::Evict: Asset evicted from cache: {}", handle.ToString());
    }

}

void AssetManager::EvictAll()
{
    s_AssetCache.clear();
    ENGINE_TRACE("AssetManager::EvictAll: All assets evicted from cache.");
}

void AssetManager::PurgeExpired()
{
    for (auto it = s_AssetCache.begin(); it != s_AssetCache.end(); )
    {
        if (it->second.expired())
        {
            ENGINE_TRACE("AssetManager::PurgeExpired: Purging expired asset: {}", it->first.ToString());
            it = s_AssetCache.erase(it);
        }
        else
        {
            std::next(it);
        }
    }
}