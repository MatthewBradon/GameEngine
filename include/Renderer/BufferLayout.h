#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <unordered_map>

enum class ShaderDataType
{
    Float, Float2, Float3, Float4,
    Int, Int2, Int3, Int4
};

const std::unordered_map<ShaderDataType, uint32_t> ShaderDataTypeSizeMap = {
    { ShaderDataType::Float,  sizeof(float) },
    { ShaderDataType::Float2, sizeof(float) * 2 },
    { ShaderDataType::Float3, sizeof(float) * 3 },
    { ShaderDataType::Float4, sizeof(float) * 4 },
    { ShaderDataType::Int,    sizeof(int) },
    { ShaderDataType::Int2,   sizeof(int) * 2 },
    { ShaderDataType::Int3,   sizeof(int) * 3 },
    { ShaderDataType::Int4,   sizeof(int) * 4 }
};



static uint32_t ShaderDataTypeSize(ShaderDataType type)
{
    auto it = ShaderDataTypeSizeMap.find(type);
    
    if (it != ShaderDataTypeSizeMap.end()) {
        return it->second;
    }
    return 0;

}

struct BufferElement
{
    std::string Name;
    ShaderDataType Type;
    uint32_t Size;
    uint32_t Offset;
    bool Normalized;

    BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
        : Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
    {}
};

class BufferLayout
{
public:
    BufferLayout() {}

    BufferLayout(const std::initializer_list<BufferElement>& elements);
    inline uint32_t GetStride() const { return m_Stride; }
    inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
private:
    void CalculateOffsetsAndStride();

    std::vector<BufferElement> m_Elements;
    uint32_t m_Stride = 0;
};