#pragma once

#include "Core/Window.h"
#include "Core/Log.h"
#include "Platform/SdlAdapter.h"

#include <SDL3/SDL.h>

Window::Window(uint32_t width, uint32_t height, const char* title)
{
    if (!SdlAdapter::InitializeVideo()) {
        ENGINE_LOG("Failed to initialize SDL: {}", SDL_GetError());
        return;
    }

    m_Handle = SdlAdapter::CreateSDLWindow(title, width, height);
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