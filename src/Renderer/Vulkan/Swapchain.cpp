#include "Renderer/Vulkan/Swapchain.h"
#include "Core/Log.h"
#include <algorithm>
#include <array>

void Swapchain::Initialize(VulkanContext& context, Window* window)
{
    m_Context = &context;
    m_WindowHandle = window;

    CreateSwapchain();

    CreateImageViews();

    CreateDepthResources();
}

void Swapchain::Shutdown()
{
    DestroyDepthResources();

    DestroyImageViews();

    DestroySwapchain();
}

void Swapchain::Resize()
{
    vkDeviceWaitIdle(m_Context->GetDevice());

    DestroyDepthResources();
    DestroyImageViews();
    DestroySwapchain();

    CreateSwapchain();
    CreateImageViews();
    CreateDepthResources();
}

Swapchain::Image Swapchain::AcquireNextImage(VkSemaphore imageAvailableSemaphore)
{
    uint32_t imageIndex;
    VULKAN_ASSERT(vkAcquireNextImageKHR(m_Context->GetDevice(), m_Swapchain, UINT64_MAX, imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex));

    return {
        .index = imageIndex,
        .image = m_Images[imageIndex],
        .view = m_ImageViews[imageIndex]
    };
}

void Swapchain::Present(uint32_t imageIndex, VkSemaphore renderFinishedSemaphore)
{
    VkPresentInfoKHR presentInfo{
        .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = &renderFinishedSemaphore,
        .swapchainCount = 1,
        .pSwapchains = &m_Swapchain,
        .pImageIndices = &imageIndex
    };

    VULKAN_ASSERT(vkQueuePresentKHR(m_Context->GetGraphicsQueue(), &presentInfo));
}

void Swapchain::CreateSwapchain()
{
    VkPhysicalDevice physicalDevice = m_Context->GetPhysicalDevice();
    VkDevice device = m_Context->GetDevice();


    VkSurfaceCapabilitiesKHR surfaceCapabilities{};
    VULKAN_ASSERT(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, m_Context->GetSurface(), &surfaceCapabilities));


    // Query the supported surface formats
    uint32_t formatCount;

    VULKAN_ASSERT(vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, m_Context->GetSurface(), &formatCount, nullptr));
    std::vector<VkSurfaceFormatKHR> formats(formatCount);

    VULKAN_ASSERT(vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, m_Context->GetSurface(), &formatCount, formats.data()));

    VkSurfaceFormatKHR surfaceFormat = ChooseSurfaceFormat(formats);


    // Query the supported present modes
    uint32_t presentModeCount;
    VULKAN_ASSERT(vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, m_Context->GetSurface(), &presentModeCount, nullptr));

    std::vector<VkPresentModeKHR> presentModes(presentModeCount);
    VULKAN_ASSERT(vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, m_Context->GetSurface(), &presentModeCount, presentModes.data()));

    VkPresentModeKHR presentMode = ChoosePresentMode(presentModes);


    m_Extent = surfaceCapabilities.currentExtent;

    if (m_Extent.width == UINT32_MAX)
    {
        m_Extent.width = m_WindowHandle->GetWidth();
        m_Extent.height = m_WindowHandle->GetHeight();
    }

    // Image count
    uint32_t imageCount = surfaceCapabilities.minImageCount + 1;

    if (surfaceCapabilities.maxImageCount > 0 && imageCount > surfaceCapabilities.maxImageCount)
    {
        imageCount = surfaceCapabilities.maxImageCount;
    }

    
    // Create the swapchain
    VkSwapchainCreateInfoKHR swapchainCreateInfo{
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .surface = m_Context->GetSurface(),
        .minImageCount = imageCount,
        .imageFormat = surfaceFormat.format,
        .imageColorSpace = surfaceFormat.colorSpace,
        .imageExtent = m_Extent,
        .imageArrayLayers = 1,
        .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT |
            VK_IMAGE_USAGE_TRANSFER_DST_BIT,
        .imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
        .preTransform = surfaceCapabilities.currentTransform,
        .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
        .presentMode = presentMode,
        .clipped = VK_TRUE,
        .oldSwapchain = VK_NULL_HANDLE
    };

    VULKAN_ASSERT(vkCreateSwapchainKHR(device, &swapchainCreateInfo, nullptr, &m_Swapchain));

    m_ColorFormat = surfaceFormat.format;
}

void Swapchain::DestroySwapchain()
{
    if (m_Swapchain != VK_NULL_HANDLE)
    {
        vkDestroySwapchainKHR(m_Context->GetDevice(), m_Swapchain, nullptr);
        m_Swapchain = VK_NULL_HANDLE;
    }
}

void Swapchain::CreateImageViews()
{
    VkDevice device = m_Context->GetDevice();

    uint32_t imageCount{0};

    vkGetSwapchainImagesKHR(device, m_Swapchain, &imageCount, nullptr);

    m_Images.resize(imageCount);

    vkGetSwapchainImagesKHR(device, m_Swapchain, &imageCount, m_Images.data());

    m_ImageViews.resize(imageCount);

    for (uint32_t i = 0; i < imageCount; ++i)
    {
        VkImageViewCreateInfo viewCreateInfo{
            .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
            .image = m_Images[i],
            .viewType = VK_IMAGE_VIEW_TYPE_2D,
            .format = m_ColorFormat,
            .subresourceRange = {
                .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                .baseMipLevel = 0,
                .levelCount = 1,
                .baseArrayLayer = 0,
                .layerCount = 1
            }
        };

        VULKAN_ASSERT(vkCreateImageView(device, &viewCreateInfo, nullptr, &m_ImageViews[i]));
    }
}

void Swapchain::DestroyImageViews()
{
    for (auto imageView : m_ImageViews)
    {
        vkDestroyImageView(m_Context->GetDevice(), imageView, nullptr);
    }
    m_ImageViews.clear();
}

void Swapchain::CreateDepthResources()
{
    m_DepthFormat = VK_FORMAT_D32_SFLOAT;

    VkImageCreateInfo imageCreateInfo{
        .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        .imageType = VK_IMAGE_TYPE_2D,
        .format = m_DepthFormat,
        .extent = {
            .width = m_Extent.width,
            .height = m_Extent.height,
            .depth = 1
        },
        .mipLevels = 1,
        .arrayLayers = 1,
        .samples = VK_SAMPLE_COUNT_1_BIT,
        .tiling = VK_IMAGE_TILING_OPTIMAL,
        .usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
        .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED
    };

    VmaAllocationCreateInfo allocCreateInfo{
        .flags = VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT,
        .usage = VMA_MEMORY_USAGE_AUTO,
        .requiredFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
    };

    VULKAN_ASSERT(vmaCreateImage(m_Context->GetAllocator(), &imageCreateInfo, &allocCreateInfo, &m_DepthImage, &m_DepthImageAllocation, nullptr));

    VkImageViewCreateInfo viewCreateInfo{
        .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        .image = m_DepthImage,
        .viewType = VK_IMAGE_VIEW_TYPE_2D,
        .format = m_DepthFormat,
        .subresourceRange = {
            .aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT,
            .baseMipLevel = 0,
            .levelCount = 1,
            .baseArrayLayer = 0,
            .layerCount = 1
        }
    };

    VULKAN_ASSERT(vkCreateImageView(m_Context->GetDevice(), &viewCreateInfo, nullptr, &m_DepthImageView));

}

void Swapchain::DestroyDepthResources()
{
    if (m_DepthImageView != VK_NULL_HANDLE)
    {
        vkDestroyImageView(m_Context->GetDevice(), m_DepthImageView, nullptr);
        m_DepthImageView = VK_NULL_HANDLE;
    }

    if (m_DepthImage != VK_NULL_HANDLE)
    {
        vmaDestroyImage(m_Context->GetAllocator(), m_DepthImage, m_DepthImageAllocation);
        m_DepthImage = VK_NULL_HANDLE;
        m_DepthImageAllocation = VK_NULL_HANDLE;
    }
}


VkSurfaceFormatKHR ChooseSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& formats)
{
    constexpr std::array preferredFormats
    {
        VK_FORMAT_B8G8R8A8_UNORM,
        VK_FORMAT_R8G8B8A8_UNORM,
        VK_FORMAT_A2B10G10R10_UNORM_PACK32
    };

    for (VkFormat preferred : preferredFormats)
    {
        for (const auto& available : formats)
        {
            if (available.format == preferred && available.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
            {
                return available;
            }
        }
    }

    return formats.front();
}


VkPresentModeKHR ChoosePresentMode(const std::vector<VkPresentModeKHR>& presentModes)
{
    constexpr std::array preferredModes
    {
        VK_PRESENT_MODE_MAILBOX_KHR,
        VK_PRESENT_MODE_FIFO_KHR
    };

    for (VkPresentModeKHR preferred : preferredModes)
    {
        if (std::find(presentModes.begin(), presentModes.end(), preferred) != presentModes.end())
        {
            return preferred;
        }
    }

    return VK_PRESENT_MODE_FIFO_KHR;
}