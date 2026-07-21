#include "Engine.h"
#include "Core/Window.h"
#include "Core/Log.h"
#include "Core/Input.h"
#include "Core/Event/EngineInput.h"
#include "Core/Assets/AssetManager.h"

#include <memory>
#include <random>

Engine::Engine() {
    Log::Init();
    
    m_Window = std::make_unique<Window>(800, 600, "Sigil");

    ENGINE_LOG("Engine initialized successfully.");
    
}



Engine::~Engine() {
    // Destructor code here
}

void Engine::Initialize() {
    AssetManager::Initalize("assets/assets.yaml");
    ENGINE_LOG("Asset Manager initialized successfully.");



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

        if (Input::IsKeyPressed(EngineInput::KEY_ESCAPE))
        {
            ENGINE_LOG("Escape key pressed. Closing window.");
            m_Window->CloseWindow();
        }

        m_Window->GetEventQueue().Clear();

    }
}

void Engine::Shutdown() {
    // Cleanup code here
}