#include "Core/Input.h"
#include "Core/Log.h"
#include "Core/Event/EventDispatcher.h"
#include "Core/Event/KeyEvent.h"
#include "Core/Event/MouseEvent.h"

#include <cstring>
#include <unordered_map>

static bool s_CurrentKeys[1024]{};
static bool s_PreviousKeys[1024]{};

static double s_MouseX{0.0};
static double s_MouseY{0.0};

static double s_LastMouseX{0.0};
static double s_LastMouseY{0.0};

static double s_MouseDeltaX{0.0};
static double s_MouseDeltaY{0.0};

static double s_ScrollDeltaX{0.0};
static double s_ScrollDeltaY{0.0};

static std::unordered_map<int, bool> s_MouseButtons;

void Input::Update()
{
    std::memcpy(s_PreviousKeys, s_CurrentKeys, sizeof(s_CurrentKeys));

    s_MouseDeltaX = s_MouseX - s_LastMouseX;
    s_MouseDeltaY = s_MouseY - s_LastMouseY;
    s_ScrollDeltaX = 0.0;
    s_ScrollDeltaY = 0.0;

    s_LastMouseX = s_MouseX;
    s_LastMouseY = s_MouseY;
}

void Input::OnEvent(Event& event)
{
    EventDispatcher dispatcher(event);

    dispatcher.Dispatch<KeyPressedEvent>(
        [](KeyPressedEvent& e)
        {
            s_CurrentKeys[e.GetKeyCode()] = true;

            ENGINE_LOG("Key pressed: {}", e.GetKeyName());

            return false;
        });

    dispatcher.Dispatch<KeyReleasedEvent>(
        [](KeyReleasedEvent& e)
        {
            s_CurrentKeys[e.GetKeyCode()] = false;

            ENGINE_LOG("Key released: {}", e.GetKeyName());

            return false;
        });

    dispatcher.Dispatch<MouseMovedEvent>(
        [](MouseMovedEvent& e)
        {
            s_MouseX =e.GetX();
            s_MouseY = e.GetY();
            return false;
        });

    dispatcher.Dispatch<MousePressedEvent>(
        [](MousePressedEvent& e)
        {
            s_MouseButtons[e.GetButton()] = true;

            ENGINE_LOG("Mouse button pressed: {}", e.GetButtonName());

            return false;
        });

    dispatcher.Dispatch<MouseReleasedEvent>(
        [](MouseReleasedEvent& e)
        {
            s_MouseButtons[e.GetButton()] = false;

            ENGINE_LOG("Mouse button released: {}", e.GetButtonName());

            return false;
        });

    dispatcher.Dispatch<MouseScrolledEvent>(
        [](MouseScrolledEvent& e)
        {
            s_ScrollDeltaX = e.GetXOffset();
            s_ScrollDeltaY = e.GetYOffset();

            ENGINE_LOG("Mouse scrolled: X offset {}, Y offset {}", e.GetXOffset(), e.GetYOffset());

            return false;
        });
}

bool Input::IsKeyDown(int keycode)
{
    return s_CurrentKeys[keycode];
}

bool Input::IsKeyPressed(int keycode)
{
    return s_CurrentKeys[keycode] &&
          !s_PreviousKeys[keycode];
}

double Input::GetMouseX()
{
    return s_MouseX;
}

double Input::GetMouseY()
{
    return s_MouseY;
}

double Input::GetMouseDeltaX()
{
    return s_MouseDeltaX;
}

double Input::GetMouseDeltaY()
{
    return s_MouseDeltaY;
}

bool Input::IsMouseButtonDown(int button)
{
    auto it{s_MouseButtons.find(button)};
    return it != s_MouseButtons.end() ? it->second : false;
}

bool Input::IsMouseButtonPressed(int button)
{
    static std::unordered_map<int, bool> previousMouseButtons;

    bool isDown = IsMouseButtonDown(button);
    bool wasDown = previousMouseButtons[button];

    previousMouseButtons[button] = isDown;

    return isDown && !wasDown;
}

double Input::GetScrollDeltaX()
{
    return s_ScrollDeltaX;
}

double Input::GetScrollDeltaY()
{
    return s_ScrollDeltaY;
}