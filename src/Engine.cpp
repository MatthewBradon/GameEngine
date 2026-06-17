#include "Engine.h"
#include "Core/Window.h"
#include "Core/Log.h"
#include "Core/Input.h"
#include "Core/Event/EngineInput.h"
#include "Platform/GLFWInputBridge.h"
#include "Core/Assets/AssetManager.h"
#include "Renderer/Shader.h"
#include "Renderer/VertexArrayObject.h"
#include "Renderer/VertexBufferObject.h"
#include "Renderer/RenderCommand.h"
#include "Renderer/BufferLayout.h"
#include <GLFW/glfw3.h>
#include <memory>
#include <random>


float vertices[] = {
    // positions         // colors
    0.0f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f
};
        


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
    std::shared_ptr<VertexArrayObject> vao = VertexArrayObject::Create();
    std::shared_ptr<VertexBufferObject> vbo = VertexBufferObject::Create(vertices, sizeof(vertices));
    std::shared_ptr<Shader> shader;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);

    // Initial random colors per-vertex (already in `vertices`) can be changed on click

    BufferLayout layout = {
        { ShaderDataType::Float3, "position" },
        { ShaderDataType::Float3, "color" }
    };

    vbo->SetLayout(layout);

    vao->Bind();
    vao->AddVertexBuffer(vbo);
    
    shader = AssetManager::Get<Shader>("BasicShader");

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

        if (Input::IsMouseButtonPressed(EngineInput::MOUSE_LEFT))
        {
            // Generate new random colors for each vertex and update the VBO
            for (int i = 0; i < 3; ++i) {
                float r = dis(gen);
                float g = dis(gen);
                float b = dis(gen);
                // color offset: each vertex has 6 floats (3 pos + 3 color)
                int base = i * 6 + 3; // color starts after position
                vertices[base + 0] = r;
                vertices[base + 1] = g;
                vertices[base + 2] = b;
            }
            vbo->SetData(vertices, sizeof(vertices));
        }

        shader->Bind();
        RenderCommand::Clear();
        RenderCommand::DrawArrays(3);

        shader->Unbind();

        m_Window->GetEventQueue().Clear();




        m_Window->SwapBuffers();
    }
}

void Engine::Shutdown() {
    // Cleanup code here
}