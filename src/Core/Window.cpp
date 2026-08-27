#pragma once

#include "Core/Window.h"
#include "Core/Log.h"
#include "Platform/SdlAdapter.h"

Window::Window(uint32_t width, uint32_t height, const char* title)
{
    ENGINE_ASSERT(SDL_Init(SDL_INIT_VIDEO), "Failed to initialize SDL: {}", SDL_GetError());

    m_Handle = SDL_CreateWindow(title, static_cast<int>(width), static_cast<int>(height), SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);

    ENGINE_ASSERT(m_Handle != nullptr, "Failed to create SDL window: {}", SDL_GetError());

    m_Width = width;
    m_Height = height;

    ENGINE_LOG("Window created successfully.");
}

void Window::PollEvents()
{
    SdlAdapter::PollEvents(m_EventQueue, m_ShouldClose, m_Width, m_Height);
}

bool Window::ShouldClose() const
{
    return m_ShouldClose;
}

bool Window::CloseWindow()
{
    m_ShouldClose = true;
    return true;
}

EventQueue& Window::GetEventQueue()
{
    return m_EventQueue;
}

Window::~Window()
{
    if (m_Handle) {
        SDL_DestroyWindow(m_Handle);
        ENGINE_LOG("Window destroyed.");
    }
}