
#pragma once

#include <memory>

class Window;

class Engine
{
public:
    Engine();
    ~Engine();
    void Initialize();
    void Run();
    void Shutdown();
private:
    std::unique_ptr<Window> m_Window;
};