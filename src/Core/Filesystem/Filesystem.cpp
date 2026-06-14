#include "Core/Filesystem/Filesystem.h"

#include <fstream>

Buffer FileSystem::ReadBinary(const std::string& path)
{
    std::ifstream file(path, std::ios::binary);

    if (!file.is_open())
    {
        return {};
    }
        

    file.seekg(0, std::ios::end);

    size_t size = file.tellg();

    file.seekg(0, std::ios::beg);

    Buffer buffer(size);

    file.read((char*)buffer.Data(), size);

    return buffer;
}

#include <sstream>

std::string FileSystem::ReadText(const std::string& path)
{
    std::ifstream file(path);

    if (!file.is_open()) 
    {
        return {};
    }
        

    std::stringstream stream;

    stream << file.rdbuf();

    return stream.str();
}

bool FileSystem::Exists(const std::string& path)
{
    std::ifstream file(path);
    return file.is_open();
}