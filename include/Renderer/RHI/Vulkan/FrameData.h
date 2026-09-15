#pragma once

#include <volk.h>

class VulkanContext;

class FrameData
{
public:

    ~FrameData() { Shutdown(); }

    void Initialize(VulkanContext& context);
    void Shutdown();

    void Wait();
    void Reset();

    void Begin();
    void End();

    VkCommandBuffer GetCommandBuffer() const
    {
        return m_CommandBuffer;
    }

    VkSemaphore GetImageAvailableSemaphore() const
    {
        return m_ImageAvailableSemaphore;
    }

    VkSemaphore GetRenderFinishedSemaphore() const
    {
        return m_RenderFinishedSemaphore;
    }

    VkFence GetRenderFence() const
    {
        return m_RenderFence;
    }

private:

    VulkanContext* m_Context{nullptr};

    VkCommandPool m_CommandPool{VK_NULL_HANDLE};
    VkCommandBuffer m_CommandBuffer{VK_NULL_HANDLE};

    VkFence m_RenderFence{VK_NULL_HANDLE};

    VkSemaphore m_ImageAvailableSemaphore{VK_NULL_HANDLE};
    VkSemaphore m_RenderFinishedSemaphore{VK_NULL_HANDLE};
};