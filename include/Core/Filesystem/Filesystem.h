#pragma once

#include "Buffer.h"

#include <string>

class FileSystem
{
public:
    static Buffer ReadBinary(const std::string& path);

    static std::string ReadText(const std::string& path);

    static std::string GetFileExtension(const std::string& path);

    static bool Exists(const std::string& path);
};