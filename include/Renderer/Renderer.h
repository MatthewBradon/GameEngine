#pragma once

#include "Core/Window.h"
#include "Renderer/Vulkan/VulkanContext.h"
#include "Renderer/Vulkan/Swapchain.h"

#include <glm/glm.hpp>
#include <array>

class Camera;
class MeshHandle;
class MaterialHandle;


class Renderer
{
public:

    void Initialize(Window&);

    void Shutdown();

    void BeginFrame(const Camera&);

    void EndFrame();

    void Submit(MeshHandle, MaterialHandle, const glm::mat4& transform);

private:
    VulkanContext m_Context;
    Swapchain m_Swapchain;

};