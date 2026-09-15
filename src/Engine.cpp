#include "Engine.h"
#include "Core/Window.h"
#include "Core/Log.h"
#include "Core/Input.h"
#include "Core/Event/EngineInput.h"
#include "Core/Assets/AssetManager.h"
#include "Renderer/Renderer.h"
#include <memory>
#include <random>

void Engine::Initialize() {

    Log::Init();
    
    m_Window = std::make_unique<Window>(800, 600, "Sigil");

    ENGINE_LOG("Window initialized successfully.");

    m_Renderer.Initialize(*m_Window);
    AssetManager::Initialize("assets/assets.yaml");
    ENGINE_LOG("Asset Manager initialized successfully.");
    Input::SetWindow(m_Window.get());
}

void Engine::Run()
{
    AssetManager::PrintCacheStatus();
    m_Renderer.LoadBasicShader();
    AssetManager::PrintCacheStatus();
    
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
    ENGINE_LOG("Shutting down engine...");
    
    m_Window.reset();

    m_Renderer.Shutdown();
    AssetManager::Shutdown();
}
