#include "Renderer/Vulkan/VulkanContext.h"

#include <SDL3/SDL_vulkan.h>
#define VOLK_IMPLEMENTATION
#include <volk.h>
#include <vulkan/vulkan.h>

#define VMA_IMPLEMENTATION
#include <vma/vk_mem_alloc.h>

#include "Core/Log.h"


#include <ktx.h>
#include <ktxvulkan.h>

void VulkanContext::Initialize(Window* window)
{
    m_WindowHandle = window->GetHandle();

    volkInitialize();

    ENGINE_ASSERT(SDL_Vulkan_LoadLibrary(nullptr), "Failed to load Vulkan library: {}", SDL_GetError());

    CreateInstance();
    
    CreateSurface();

    PickPhysicalDevice();
    
    FindQueueFamilyIndices();
    ENGINE_ASSERT(SDL_Vulkan_GetPresentationSupport(m_Instance, m_PhysicalDevice, m_GraphicsQueueFamily), "SDL_Vulkan_GetPresentationSupport failed: {}", SDL_GetError());

    vkGetDeviceQueue(m_Device, m_GraphicsQueueFamily, 0, &m_GraphicsQueue);

    CreateDevice();
    
    CreateAllocator();

    ENGINE_LOG("Vulkan context initialized successfully.");
}

void VulkanContext::CreateInstance()
{
    VkApplicationInfo appInfo{
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = "Vulkan Experiment",
        .apiVersion = VK_API_VERSION_1_4
    };

     // Get instance extensions
    uint32_t instanceExtensionsCount{0};
    const char* const* instanceExtensions{SDL_Vulkan_GetInstanceExtensions(&instanceExtensionsCount)};

    std::vector<const char *> requestedExtentions
    {
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME
    };

    for (int i =0; i < instanceExtensionsCount; i++)
    {
        requestedExtentions.push_back(instanceExtensions[i]);
    }

    std::vector<const char*> requestedLayers
    {
        "VK_LAYER_KHRONOS_validation"
    };    

    VkDebugUtilsMessengerCreateInfoEXT debugInfo = {
        .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
        .messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                        VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                        VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
        .messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                    VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
        .pfnUserCallback = debugCallback
    };


        VkInstanceCreateInfo instanceCreateInfo{
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pNext = &debugInfo,
        .pApplicationInfo = &appInfo,
        .enabledLayerCount = static_cast<uint32_t>(requestedLayers.size()),
        .ppEnabledLayerNames = requestedLayers.data(),
        .enabledExtensionCount = static_cast<uint32_t>(requestedExtentions.size()),
        .ppEnabledExtensionNames = requestedExtentions.data(),
    };

    // Create Instance
    VULKAN_ASSERT(vkCreateInstance(&instanceCreateInfo, nullptr, &m_Instance));

    volkLoadInstance(m_Instance);

}

void VulkanContext::Shutdown()
{
    if (m_Allocator)
    {
        vmaDestroyAllocator(m_Allocator);
    }

    if (m_Device)
    {
        vkDestroyDevice(m_Device, nullptr);
    }

    if (m_Surface)
    {
        vkDestroySurfaceKHR(m_Instance, m_Surface, nullptr);
    }
    
    if (m_DebugMessenger)
    {
        vkDestroyDebugUtilsMessengerEXT(m_Instance, m_DebugMessenger, nullptr);
    }

    if (m_Instance)
    {
        vkDestroyInstance(m_Instance, nullptr);
    }
}

void VulkanContext::CreateSurface()
{
    ENGINE_ASSERT(SDL_Vulkan_CreateSurface(m_WindowHandle, m_Instance, nullptr, &m_Surface), "SDL_Vulkan_CreateSurface failed: {}", SDL_GetError());
}

void VulkanContext::PickPhysicalDevice()
{
    uint32_t deviceCount{0};
    VULKAN_ASSERT(vkEnumeratePhysicalDevices(m_Instance, &deviceCount, nullptr));
    
    std::vector<VkPhysicalDevice> devices(deviceCount);
    VULKAN_ASSERT(vkEnumeratePhysicalDevices(m_Instance, &deviceCount, devices.data()));



    if (deviceCount > 0)
    {
        m_PhysicalDevice = devices[0];

        // Look through the devices and find a discrete GPU if possible
        for (auto &pDevice : devices)
        {
            VkPhysicalDeviceProperties2 deviceProperties{
                .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2 
            };
            vkGetPhysicalDeviceProperties2(pDevice, &deviceProperties);

            ENGINE_LOG("Found Device: {}", deviceProperties.properties.deviceName);

            if (deviceProperties.properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
            {
                ENGINE_LOG("Selected Device: {}", deviceProperties.properties.deviceName);
                m_PhysicalDevice = pDevice;
                break;
            }
        }
    }

    ENGINE_ASSERT(m_PhysicalDevice != VK_NULL_HANDLE, "No suitable physical device found");
    
}

void VulkanContext::FindQueueFamilyIndices()
{
    uint32_t queueFamilyCount{0};
    vkGetPhysicalDeviceQueueFamilyProperties(m_PhysicalDevice, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(m_PhysicalDevice, &queueFamilyCount, queueFamilies.data());

    for (uint32_t i = 0; i < queueFamilies.size(); i++)
    {
        if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            m_GraphicsQueueFamily = i;
            break;
        }
    }

    ENGINE_ASSERT(m_GraphicsQueueFamily != UINT32_MAX, "No suitable graphics queue family found");

}

void VulkanContext::CreateDevice()
{
        
    VkDeviceQueueCreateInfo queueCreateInfo{
        .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        .queueFamilyIndex = m_GraphicsQueueFamily, 
        .queueCount = 1, 
        .pQueuePriorities = &qfpriorities
    };

    VkPhysicalDeviceVulkan12Features enabledVk12Features{
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES, 
        .descriptorIndexing = true, 
        .shaderSampledImageArrayNonUniformIndexing = true, 
        .descriptorBindingVariableDescriptorCount = true, 
        .runtimeDescriptorArray = true, 
        .bufferDeviceAddress = true 
    };
	
    VkPhysicalDeviceVulkan13Features enabledVk13Features{ 
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES, 
        .pNext = &enabledVk12Features, 
        .synchronization2 = true, 
        .dynamicRendering = true 
    };

    VkPhysicalDeviceVulkan14Features enabledVk14Features{
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_4_FEATURES,
        .pNext = &enabledVk13Features
    };
	
    VkPhysicalDeviceFeatures enabledVk10Features{
        .samplerAnisotropy = VK_TRUE
    }; 

	const std::vector<const char*> deviceExtensions{VK_KHR_SWAPCHAIN_EXTENSION_NAME};

	VkDeviceCreateInfo deviceCreateInfo{
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.pNext = &enabledVk14Features,
		.queueCreateInfoCount = 1,
		.pQueueCreateInfos = &queueCreateInfo,
		.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size()),
		.ppEnabledExtensionNames = deviceExtensions.data(),
		.pEnabledFeatures = &enabledVk10Features
	};

    VULKAN_ASSERT(vkCreateDevice(m_PhysicalDevice, &deviceCreateInfo, nullptr, &m_Device));
}

void VulkanContext::CreateAllocator()
{
    VmaVulkanFunctions vkFunctions{
        .vkGetInstanceProcAddr = vkGetInstanceProcAddr,
        .vkGetDeviceProcAddr = vkGetDeviceProcAddr,
        .vkCreateImage = vkCreateImage
    };

    VmaAllocatorCreateInfo allocatorCreateInfo{
        .flags = VMA_ALLOCATOR_CREATE_BUFFER_DEVICE_ADDRESS_BIT,
        .physicalDevice = m_PhysicalDevice,
        .device = m_Device,
        .pVulkanFunctions = &vkFunctions,
        .instance = m_Instance
    };

    VULKAN_ASSERT(vmaCreateAllocator(&allocatorCreateInfo, &m_Allocator));
}


VkInstance VulkanContext::GetInstance() const
{
    ENGINE_ASSERT(m_Instance != VK_NULL_HANDLE, "Vulkan instance is not initialized");
    return m_Instance;
}

VkDevice VulkanContext::GetDevice() const
{
    ENGINE_ASSERT(m_Device != VK_NULL_HANDLE, "Device is not initialized");
    return m_Device;
}

VkPhysicalDevice VulkanContext::GetPhysicalDevice() const
{
    ENGINE_ASSERT(m_PhysicalDevice != VK_NULL_HANDLE, "Physical device is not initialized");
    return m_PhysicalDevice;
}

VkQueue VulkanContext::GetGraphicsQueue() const
{
    ENGINE_ASSERT(m_GraphicsQueue != VK_NULL_HANDLE, "Graphics queue is not initialized");
    return m_GraphicsQueue;
}

uint32_t VulkanContext::GetGraphicsQueueFamily() const
{
    ENGINE_ASSERT(m_GraphicsQueueFamily != UINT32_MAX, "Graphics queue family index is not set");
    return m_GraphicsQueueFamily;
}

VmaAllocator VulkanContext::GetAllocator() const
{
    ENGINE_ASSERT(m_Allocator != VK_NULL_HANDLE, "Vulkan allocator is not initialized");
    return m_Allocator;
}

VkSurfaceKHR VulkanContext::GetSurface() const
{
    ENGINE_ASSERT(m_Surface != VK_NULL_HANDLE, "Vulkan surface is not initialized");
    return m_Surface;
}

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData) {

    if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
    {
        ENGINE_ERROR("Vulkan Debug Callback: {}", pCallbackData->pMessage);
    }
    else if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT)
    {
        ENGINE_TRACE("Vulkan Debug Callback: {}", pCallbackData->pMessage);
    }
    else
    {
        ENGINE_LOG("Vulkan Debug Callback: {}", pCallbackData->pMessage);
    }

    return VK_FALSE;
}