#pragma once

#include <memory>

#include "Renderer/Renderer.h"

class Window;

class Engine
{
public:
    void Initialize();
    void Run();
    void Shutdown();
private:
    std::unique_ptr<Window> m_Window;
    Renderer m_Renderer;
};
