#pragma once

#ifndef VK_NO_PROTOTYPES
#define VK_NO_PROTOTYPES
#endif
#include <vulkan/vulkan.h>
#include <string_view>

enum class ShaderStage
{
    Vertex,
    Fragment,
    Compute
};

inline VkShaderStageFlagBits ToVkShaderStage(
    ShaderStage stage)
{
    switch (stage)
    {
        case ShaderStage::Vertex:
            return VK_SHADER_STAGE_VERTEX_BIT;

        case ShaderStage::Fragment:
            return VK_SHADER_STAGE_FRAGMENT_BIT;

        case ShaderStage::Compute:
            return VK_SHADER_STAGE_COMPUTE_BIT;
    }

    return VK_SHADER_STAGE_FLAG_BITS_MAX_ENUM;
}

inline std::string_view ShaderStageToString(
    ShaderStage stage)
{
    switch (stage)
    {
        case ShaderStage::Vertex:
            return "vertex";

        case ShaderStage::Fragment:
            return "fragment";

        case ShaderStage::Compute:
            return "compute";
    }

    return "unknown";
}

inline bool ShaderStageFromString(
    std::string_view value,
    ShaderStage& stage)
{
    if (value == "vertex")
    {
        stage = ShaderStage::Vertex;
        return true;
    }

    if (value == "fragment")
    {
        stage = ShaderStage::Fragment;
        return true;
    }

    if (value == "compute")
    {
        stage = ShaderStage::Compute;
        return true;
    }

    return false;
}