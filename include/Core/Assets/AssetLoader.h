#pragma once
#include "AssetHandle.h"
#include <memory>

template<typename T>
class AssetLoader
{
public:
    static std::shared_ptr<T> Load(const AssetHandle& handle);
};