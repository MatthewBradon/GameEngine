#pragma once

#include "Core/Event/EventQueue.h"

struct GLFWwindow;

class Window
{
public:
    Window(uint32_t width, uint32_t height, const char* title);

    void PollEvents();
    void SwapBuffers();

    bool ShouldClose() const;
    bool CloseWindow();

    EventQueue& GetEventQueue();

private:
    GLFWwindow* m_Handle;

    EventQueue m_EventQueue;
};