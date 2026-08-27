#pragma once

#include <vulkan/vulkan.h>
#include<vk_mem_alloc.h>

class VulkanContext;

class Image
{
public:
    void Create(VulkanContext& context, VkImageCreateInfo& imageCreateInfo, VmaAllocationCreateInfo& allocationCreateInfo);
    void Destroy();
    ~Image() { Destroy(); }


    VkImage GetHandle() const { return m_Image; }
    VkImageView GetView() const { return m_View; }
    VmaAllocation GetAllocation() const { return m_Allocation; }

private:
    VkDevice m_Device{VK_NULL_HANDLE};
    VmaAllocator m_Allocator{VK_NULL_HANDLE};
    VkImage m_Image{VK_NULL_HANDLE};
    VkImageView m_View{VK_NULL_HANDLE};
    VmaAllocation m_Allocation{VK_NULL_HANDLE};
};