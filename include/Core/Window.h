#pragma once

#include <SDL3/SDL.h>
#include <cstdint>
#include "Core/Event/EventQueue.h"


class Window
{
public:
    Window(uint32_t width, uint32_t height, const char* title);

    void PollEvents();

    bool ShouldClose() const;
    bool CloseWindow();

    SDL_Window* GetHandle() const { return m_Handle; }

    void updateExtents();

    uint32_t GetWidth() const { return m_Width; }
    uint32_t GetHeight() const { return m_Height; }


    EventQueue& GetEventQueue();

    ~Window();

private:
    SDL_Window* m_Handle{nullptr};
    EventQueue m_EventQueue;
    bool m_ShouldClose{false};

    uint32_t m_Width;
    uint32_t m_Height;
};