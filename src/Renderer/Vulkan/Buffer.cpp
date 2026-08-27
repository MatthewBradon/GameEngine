#include "Renderer/Vulkan/Buffer.h"
#include "Renderer/Vulkan/VulkanContext.h"
#include "Core/Log.h"


#include <cstring>
#include <stdexcept>

void Buffer::Create(VulkanContext& context, const BufferCreateDesc& desc)
{
    m_Allocator = context.GetAllocator();
    m_Size = desc.size;

    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType =
        VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;

    bufferInfo.size = desc.size;
    bufferInfo.usage = desc.usage;
    bufferInfo.sharingMode =
        VK_SHARING_MODE_EXCLUSIVE;

    VmaAllocationCreateInfo allocationInfo{};
    allocationInfo.usage = desc.memoryUsage;
    allocationInfo.flags = desc.allocationFlags;

    VkResult result = vmaCreateBuffer(
        m_Allocator,
        &bufferInfo,
        &allocationInfo,
        &m_Buffer,
        &m_Allocation,
        nullptr);

    VULKAN_ASSERT(result, "Failed to create Vulkan buffer");
}

void Buffer::Destroy()
{
    if (m_Buffer != VK_NULL_HANDLE)
    {
        vmaDestroyBuffer(
            m_Allocator,
            m_Buffer,
            m_Allocation);
    }

    m_Buffer = VK_NULL_HANDLE;
    m_Allocation = nullptr;
    m_Allocator = nullptr;
    m_Size = 0;
    m_MappedData = nullptr;
}

void* Buffer::Map()
{
    if (m_MappedData != nullptr)
    {
        return m_MappedData;
    }

    VkResult result = vmaMapMemory(
        m_Allocator,
        m_Allocation,
        &m_MappedData);

    VULKAN_ASSERT(result, "Failed to map Vulkan buffer memory");

    return m_MappedData;
}

void Buffer::Unmap()
{
    if (m_MappedData != nullptr)
    {
        vmaUnmapMemory(
            m_Allocator,
            m_Allocation);

        m_MappedData = nullptr;
    }
}

void Buffer::UploadData(
    const void* data,
    VkDeviceSize size,
    VkDeviceSize offset)
{
    void* mapped = Map();

    auto* destination =
        static_cast<uint8_t*>(mapped) + offset;

    std::memcpy(
        destination,
        data,
        static_cast<size_t>(size));

    // Depending on allocation/memory type, VMA may need this.
    vmaFlushAllocation(
        m_Allocator,
        m_Allocation,
        offset,
        size);
}