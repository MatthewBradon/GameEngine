#pragma once

#include <string>

class Asset
{
public:
    virtual ~Asset() = default;

    const std::string& GetPath() const
    {
        return m_Path;
    }

protected:
    std::string m_Path;
};