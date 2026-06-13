#pragma once

#include "Core/Window.h"
#include "Core/Log.h"
#include "Platform/GLFWInputBridge.h"
#include "Renderer/RenderCommand.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Window::Window(uint32_t width, uint32_t height, const char* title)
{
    glfwInit();

    m_Handle = glfwCreateWindow(width, height, title, nullptr, nullptr);

    glfwMakeContextCurrent(m_Handle);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        ENGINE_ERROR("Failed to initialize GLAD");
        return;
    }

    GLFWInputBridge::Attach(m_Handle, &m_EventQueue);
    
    RenderCommand::Init();
    RenderCommand::SetViewport(0, 0, width, height);
}

void Window::PollEvents()
{
    glfwPollEvents();
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(m_Handle);
}

bool Window::ShouldClose() const
{
    return glfwWindowShouldClose(m_Handle);
}

bool Window::CloseWindow()
{
    glfwSetWindowShouldClose(m_Handle, true);
    return true;
}

EventQueue& Window::GetEventQueue()
{
    return m_EventQueue;
}