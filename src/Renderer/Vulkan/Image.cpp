#include "Renderer/Vulkan/Image.h"
#include "Renderer/Vulkan/VulkanContext.h"

void Image::Create(VulkanContext& context, VkImageCreateInfo& imageCreateInfo, VmaAllocationCreateInfo& allocationCreateInfo)
{
    m_Allocator = context.GetAllocator();
    m_Device = context.GetDevice();

    VkResult result = vmaCreateImage(
        m_Allocator,
        &imageCreateInfo,
        &allocationCreateInfo,
        &m_Image,
        &m_Allocation,
        nullptr);

    if (result != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create Vulkan image");
    }

    // Create image view
    VkImageViewCreateInfo viewCreateInfo{
        .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        .image = m_Image,
        .viewType = VK_IMAGE_VIEW_TYPE_2D,
        .format = imageCreateInfo.format,
        .subresourceRange = {
            .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
            .baseMipLevel = 0,
            .levelCount = imageCreateInfo.mipLevels,
            .baseArrayLayer = 0,
            .layerCount = imageCreateInfo.arrayLayers
        }
    };

    result = vkCreateImageView(m_Device, &viewCreateInfo, nullptr, &m_View);
    if (result != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create Vulkan image view");
    }
}

void Image::Destroy()
{
    if (m_View != VK_NULL_HANDLE)
    {
        vkDestroyImageView(m_Device, m_View, nullptr);
        m_View = VK_NULL_HANDLE;
    }

    if (m_Image != VK_NULL_HANDLE)
    {
        vmaDestroyImage(m_Allocator, m_Image, m_Allocation);
        m_Image = VK_NULL_HANDLE;
        m_Allocation = VK_NULL_HANDLE;
    }

    m_Allocator = VK_NULL_HANDLE;
    m_Device = VK_NULL_HANDLE;
    m_View = VK_NULL_HANDLE;
    m_Image = VK_NULL_HANDLE;
    m_Allocation = VK_NULL_HANDLE;
}

