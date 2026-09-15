#include "Renderer/Renderer.h"
#include "Core/Log.h"
#include "Core/Assets/AssetManager.h"

// Triangle vertices
static const float s_TriangleVertices[] = {
    0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom vertex - Red color
    0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,   // Right vertex - Green color
    -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f   // Left vertex - Blue color
};

// Triangle indices
static const uint16_t s_TriangleIndices[] = {
    0, 1, 2 // Triangle
};


void Renderer::Initialize(Window& window)
{

}

void Renderer::Shutdown()
{
    
}

void Renderer::LoadBasicShader()
{

}

