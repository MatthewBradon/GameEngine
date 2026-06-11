#include "Engine.h"
#include "Core/Window.h"
#include "Core/Log.h"
#include "Core/Input.h"
#include "Core/Event/EngineInput.h"
#include "Platform/GLFWInputBridge.h"
#include <GLFW/glfw3.h>
#include <memory>

Engine::Engine() {
    Log::Init();
    
    m_Window = std::make_unique<Window>(800, 600, "Sigil");

    ENGINE_LOG("Engine initialized successfully.");
    
}

Engine::~Engine() {
    // Destructor code here
}

void Engine::Initialize() {
    // Initialization code here
}

void Engine::Run()
{
    while (!m_Window->ShouldClose())
    {
        Input::Update();

        m_Window->PollEvents();

        for (auto& event : m_Window->GetEventQueue().GetEvents())
        {
            Input::OnEvent(*event);
        }

        if (Input::IsKeyPressed(EngineInput::ESCAPE))
        {
            ENGINE_LOG("Escape key pressed. Closing window.");
            m_Window->CloseWindow();
        }

        m_Window->GetEventQueue().Clear();

        m_Window->SwapBuffers();
    }
}

void Engine::Shutdown() {
    // Cleanup code here
}