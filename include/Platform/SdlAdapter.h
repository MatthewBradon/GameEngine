#pragma once

#include <cstdint>

struct SDL_Window;

class EventQueue;

namespace SdlAdapter
{
    bool InitializeVideo();
    SDL_Window* CreateSDLWindow(const char* title, std::uint32_t width, std::uint32_t height);
    void SetRelativeMouseMode(SDL_Window* window, bool enabled);
    void PollEvents(EventQueue& eventQueue, bool& shouldClose, std::uint32_t& width, std::uint32_t& height);
}