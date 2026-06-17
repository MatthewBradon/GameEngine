#pragma once

#include <glm/glm.hpp>

class RenderCommand
{
public:
    static void Init();
    static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
    static void SetClearColor(const glm::vec4& color);
    static void Clear();
    static void DrawIndexed(uint32_t indexCount = 0);
    static void DrawArrays(uint32_t vertexCount = 0);
};