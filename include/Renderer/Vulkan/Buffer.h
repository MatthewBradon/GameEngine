#pragma once

#include <vulkan/vulkan.h>
#include <vk_mem_alloc.h>

class VulkanContext;

struct BufferCreateDesc
{
    VkDeviceSize size;
    VkBufferUsageFlags usage;
    VmaAllocationCreateFlags allocationFlags;
    VmaMemoryUsage memoryUsage=VMA_MEMORY_USAGE_AUTO;
};


class Buffer
{
public:
    void Create(VulkanContext& context, const BufferCreateDesc& desc);
    void Destroy();

    void* Map();
    void Unmap();

    void UploadData(const void* data, VkDeviceSize size, VkDeviceSize offset = 0);

    VkBuffer GetHandle() const { return m_Buffer; }
    VkDeviceSize GetSize() const { return m_Size; }
    bool IsValid() const { return m_Buffer != VK_NULL_HANDLE; }


private:
    VmaAllocator m_Allocator{VK_NULL_HANDLE};
    VkBuffer m_Buffer{VK_NULL_HANDLE};
    VmaAllocation m_Allocation{VK_NULL_HANDLE};

    VkDeviceSize m_Size{0};
    void* m_MappedData{nullptr};
};