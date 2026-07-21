#pragma once

#include <cstdint>

#include "Core/Event/EventQueue.h"

struct SDL_Window;

class Window
{
public:
    Window(uint32_t width, uint32_t height, const char* title);

    void PollEvents();

    bool ShouldClose() const;
    bool CloseWindow();

    void updateExtents();

    uint32_t GetWidth() const { return m_Width; }
    uint32_t GetHeight() const { return m_Height; }


    EventQueue& GetEventQueue();

private:
    SDL_Window* m_Handle;
    EventQueue m_EventQueue;
    bool m_ShouldClose{false};

    uint32_t m_Width;
    uint32_t m_Height;
};