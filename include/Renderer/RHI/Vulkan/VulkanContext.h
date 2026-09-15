#pragma once

#define VK_NO_PROTOTYPES
#include <vulkan/vulkan.h>
#include <vk_mem_alloc.h>
#include "Core/Window.h"


class VulkanContext
{
public:
    void Initialize(Window* window);
    void Shutdown();

    VkInstance GetInstance() const;
    VkDevice GetDevice() const;
    VkPhysicalDevice GetPhysicalDevice() const;
    VkQueue GetGraphicsQueue() const;
    uint32_t GetGraphicsQueueFamily() const;
    VkSurfaceKHR GetSurface() const; 

    VmaAllocator GetAllocator() const;
private:

    void CreateInstance();
    void CreateSurface();
    void PickPhysicalDevice();
    void CreateDevice();
    void CreateAllocator();
    void FindQueueFamilyIndices();

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData
    );


    SDL_Window* m_WindowHandle{nullptr} ;
    VkInstance m_Instance{VK_NULL_HANDLE};
    VkDebugUtilsMessengerEXT m_DebugMessenger{VK_NULL_HANDLE};

    VkSurfaceKHR m_Surface{VK_NULL_HANDLE};

    VkPhysicalDevice m_PhysicalDevice{VK_NULL_HANDLE};
    VkDevice m_Device{VK_NULL_HANDLE};

    VkQueue m_GraphicsQueue{VK_NULL_HANDLE};
    uint32_t m_GraphicsQueueFamily{UINT32_MAX};

    VmaAllocator m_Allocator{VK_NULL_HANDLE};

    const float qfpriorities{1.0f};

};
