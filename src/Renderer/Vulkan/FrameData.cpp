#include "Renderer/Vulkan/FrameData.h"
#include "Renderer/Vulkan/VulkanContext.h"
#include "Core/Log.h"

void FrameData::Initialize(VulkanContext& context)
{
    m_Context = &context;

    VkDevice device = m_Context->GetDevice();

    // Create command pool

    VkCommandPoolCreateInfo poolCreateInfo{
        .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
        .flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
        .queueFamilyIndex = m_Context->GetGraphicsQueueFamily()
    };

    VULKAN_ASSERT(vkCreateCommandPool(device, &poolCreateInfo, nullptr, &m_CommandPool));

    // Create command buffer
    VkCommandBufferAllocateInfo bufferAllocateInfo{
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        .commandPool = m_CommandPool,
        .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        .commandBufferCount = 1
    };

    VULKAN_ASSERT(vkAllocateCommandBuffers(device, &bufferAllocateInfo, &m_CommandBuffer));


    // Create fence
    VkFenceCreateInfo fenceCreateInfo{
        .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
        .flags = VK_FENCE_CREATE_SIGNALED_BIT
    };

    VULKAN_ASSERT(vkCreateFence(device, &fenceCreateInfo, nullptr, &m_RenderFence));


    // Create semaphores
    VkSemaphoreCreateInfo semaphoreCreateInfo{
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO
    };

    VULKAN_ASSERT(vkCreateSemaphore(device, &semaphoreCreateInfo, nullptr, &m_ImageAvailableSemaphore));
    
    VULKAN_ASSERT(vkCreateSemaphore(device, &semaphoreCreateInfo, nullptr, &m_RenderFinishedSemaphore));
}

void FrameData::Shutdown()
{
    VkDevice device = m_Context->GetDevice();

    if (m_RenderFence != VK_NULL_HANDLE)
    {
        vkDestroyFence(device, m_RenderFence, nullptr);
        m_RenderFence = VK_NULL_HANDLE;
    }

    if (m_ImageAvailableSemaphore != VK_NULL_HANDLE)
    {
        vkDestroySemaphore(device, m_ImageAvailableSemaphore, nullptr);
        m_ImageAvailableSemaphore = VK_NULL_HANDLE;
    }

    if (m_RenderFinishedSemaphore != VK_NULL_HANDLE)
    {
        vkDestroySemaphore(device, m_RenderFinishedSemaphore, nullptr);
        m_RenderFinishedSemaphore = VK_NULL_HANDLE;
    }

    if (m_CommandPool != VK_NULL_HANDLE)
    {
        vkDestroyCommandPool(device, m_CommandPool, nullptr);
        m_CommandPool = VK_NULL_HANDLE;
    }
}

void FrameData::Wait()
{
    VkDevice device = m_Context->GetDevice();

    vkWaitForFences(device, 1, &m_RenderFence, VK_TRUE, UINT64_MAX);
}

void FrameData::Reset()
{
    VkDevice device = m_Context->GetDevice();

    vkResetFences(device, 1, &m_RenderFence);

    vkResetCommandBuffer(m_CommandBuffer, 0);
}

void FrameData::Begin()
{
    VkCommandBufferBeginInfo beginInfo{
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT
    };

    VULKAN_ASSERT(vkBeginCommandBuffer(m_CommandBuffer, &beginInfo));
}

void FrameData::End()
{
    VULKAN_ASSERT(vkEndCommandBuffer(m_CommandBuffer));
}