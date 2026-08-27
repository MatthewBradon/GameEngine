#pragma once

#define VK_NO_PROTOTYPES
#include <vulkan/vulkan.h>
#include <array>
#include "Core/Window.h"
#include "VulkanContext.h"
#include <vk_mem_alloc.h>
#include <volk.h>

class Swapchain
{
public:
    
struct Image
    {
        uint32_t index;
        VkImage image;
        VkImageView view;
    };
    
    void Initialize(VulkanContext& context, Window* window);
    void Shutdown();

    void Resize();

    Swapchain::Image AcquireNextImage(VkSemaphore imageAvailableSemaphore);

    void Present(uint32_t imageIndex, VkSemaphore renderFinishedSemaphore);

    VkExtent2D GetExtent() const;
    VkFormat GetColorFormat() const;
    VkFormat GetDepthFormat() const;
    VkImage GetDepthImage() const;
    VkImageView GetDepthView() const;

private:
    void CreateSwapchain();
    void DestroySwapchain();

    void CreateImageViews();
    void DestroyImageViews();

    void CreateDepthResources();
    void DestroyDepthResources();


    VulkanContext* m_Context{nullptr};
    Window* m_WindowHandle{nullptr};
    VkExtent2D m_Extent{};

    VkSwapchainKHR m_Swapchain{VK_NULL_HANDLE};
    VkFormat m_ColorFormat{};
    VkFormat m_DepthFormat{};

    std::vector<VkImage> m_Images;
    std::vector<VkImageView> m_ImageViews;

    VkImage m_DepthImage{VK_NULL_HANDLE};
    VmaAllocation m_DepthImageAllocation{VK_NULL_HANDLE};

    // Helper functions for swapchain creation
    static VkSurfaceFormatKHR ChooseSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& formats);
    static VkPresentModeKHR ChoosePresentMode(const std::vector<VkPresentModeKHR>& presentModes);
    VkImageView m_DepthImageView{VK_NULL_HANDLE};
};