#include "Platform/GLFWInputBridge.h"

#include "Core/Event/EventQueue.h"
#include "Core/Event/KeyEvent.h"
#include "Core/Event/MouseEvent.h"
#include "Core/Event/EngineInput.h"

#include <GLFW/glfw3.h>
#include <unordered_map>

static EventQueue* s_EventQueue{nullptr};

static EngineInput::Button ToMouseButton(int glfwButton)
{
    switch (glfwButton)
    {
        case GLFW_MOUSE_BUTTON_LEFT: return EngineInput::MOUSE_LEFT;
        case GLFW_MOUSE_BUTTON_RIGHT: return EngineInput::MOUSE_RIGHT;
        case GLFW_MOUSE_BUTTON_MIDDLE: return EngineInput::MOUSE_MIDDLE;
        default: return EngineInput::UNKNOWN;
    }
}

static std::unordered_map<int, EngineInput::Button> EngineInputMap = {
    {GLFW_MOUSE_BUTTON_LEFT, EngineInput::MOUSE_LEFT},
    {GLFW_MOUSE_BUTTON_RIGHT, EngineInput::MOUSE_RIGHT},
    {GLFW_MOUSE_BUTTON_MIDDLE, EngineInput::MOUSE_MIDDLE},
    {GLFW_KEY_A, EngineInput::A},
    {GLFW_KEY_B, EngineInput::B},
    {GLFW_KEY_C, EngineInput::C},
    {GLFW_KEY_D, EngineInput::D},
    {GLFW_KEY_E, EngineInput::E},
    {GLFW_KEY_F, EngineInput::F},
    {GLFW_KEY_G, EngineInput::G},
    {GLFW_KEY_H, EngineInput::H},
    {GLFW_KEY_I, EngineInput::I},
    {GLFW_KEY_J, EngineInput::J},
    {GLFW_KEY_K, EngineInput::K},
    {GLFW_KEY_L, EngineInput::L},
    {GLFW_KEY_M, EngineInput::M},
    {GLFW_KEY_N, EngineInput::N},
    {GLFW_KEY_O, EngineInput::O},
    {GLFW_KEY_P, EngineInput::P},
    {GLFW_KEY_Q, EngineInput::Q},
    {GLFW_KEY_R, EngineInput::R},
    {GLFW_KEY_S, EngineInput::S},
    {GLFW_KEY_T, EngineInput::T},
    {GLFW_KEY_U, EngineInput::U},
    {GLFW_KEY_V, EngineInput::V},
    {GLFW_KEY_W, EngineInput::W},
    {GLFW_KEY_X, EngineInput::X},
    {GLFW_KEY_Y, EngineInput::Y},
    {GLFW_KEY_Z, EngineInput::Z},
    {GLFW_KEY_LEFT_SHIFT, EngineInput::LSHIFT},
    {GLFW_KEY_RIGHT_SHIFT, EngineInput::RSHIFT},
    {GLFW_KEY_LEFT_CONTROL, EngineInput::LCTRL},
    {GLFW_KEY_RIGHT_CONTROL, EngineInput::RCTRL},
    {GLFW_KEY_LEFT_ALT, EngineInput::LALT},
    {GLFW_KEY_RIGHT_ALT, EngineInput::RALT},
    {GLFW_KEY_SPACE, EngineInput::SPACE},
    {GLFW_KEY_APOSTROPHE, EngineInput::APOSTROPHE},
    {GLFW_KEY_COMMA, EngineInput::COMMA},
    {GLFW_KEY_MINUS, EngineInput::MINUS},
    {GLFW_KEY_PERIOD, EngineInput::PERIOD},
    {GLFW_KEY_SLASH, EngineInput::SLASH},
    {GLFW_KEY_SEMICOLON, EngineInput::SEMICOLON},
    {GLFW_KEY_EQUAL, EngineInput::EQUAL},
    {GLFW_KEY_ENTER, EngineInput::ENTER},
    {GLFW_KEY_TAB, EngineInput::TAB},
    {GLFW_KEY_BACKSPACE, EngineInput::BACKSPACE},
    {GLFW_KEY_INSERT, EngineInput::INSERT},
    {GLFW_KEY_DELETE, EngineInput::DELETE},
    {GLFW_KEY_RIGHT, EngineInput::RIGHT},
    {GLFW_KEY_LEFT, EngineInput::LEFT},
    {GLFW_KEY_DOWN, EngineInput::DOWN},
    {GLFW_KEY_UP, EngineInput::UP},
    {GLFW_KEY_PAGE_UP, EngineInput::PAGE_UP},
    {GLFW_KEY_PAGE_DOWN, EngineInput::PAGE_DOWN},
    {GLFW_KEY_HOME, EngineInput::HOME},
    {GLFW_KEY_END, EngineInput::END},
    {GLFW_KEY_CAPS_LOCK, EngineInput::CAPS_LOCK},
    {GLFW_KEY_ESCAPE, EngineInput::ESCAPE},
    {GLFW_KEY_LEFT_BRACKET, EngineInput::LEFT_BRACKET},
    {GLFW_KEY_BACKSLASH, EngineInput::BACKSLASH},
    {GLFW_KEY_RIGHT_BRACKET, EngineInput::RIGHT_BRACKET},
    {GLFW_KEY_GRAVE_ACCENT, EngineInput::GRAVEACCENT},
    {GLFW_KEY_0, EngineInput::NUMBER0},
    {GLFW_KEY_1, EngineInput::NUMBER1},
    {GLFW_KEY_2, EngineInput::NUMBER2},
    {GLFW_KEY_3, EngineInput::NUMBER3},
    {GLFW_KEY_4, EngineInput::NUMBER4},
    {GLFW_KEY_5, EngineInput::NUMBER5},
    {GLFW_KEY_6, EngineInput::NUMBER6},
    {GLFW_KEY_7, EngineInput::NUMBER7},
    {GLFW_KEY_8, EngineInput::NUMBER8},
    {GLFW_KEY_9, EngineInput::NUMBER9},
    {GLFW_KEY_F1, EngineInput::F1},
    {GLFW_KEY_F2, EngineInput::F2},
    {GLFW_KEY_F3, EngineInput::F3},
    {GLFW_KEY_F4, EngineInput::F4},
    {GLFW_KEY_F5, EngineInput::F5},
    {GLFW_KEY_F6, EngineInput::F6},
    {GLFW_KEY_F7, EngineInput::F7},
    {GLFW_KEY_F8, EngineInput::F8},
    {GLFW_KEY_F9, EngineInput::F9},
    {GLFW_KEY_F10, EngineInput::F10},
    {GLFW_KEY_F11, EngineInput::F11},
    {GLFW_KEY_F12, EngineInput::F12}
};

static EngineInput::Button GLFWToEngineKey(int glfwKey) {
    auto it = EngineInputMap.find(glfwKey);
    if (it != EngineInputMap.end())
    {
        return it->second;
    }
    return EngineInput::UNKNOWN;
}

static void KeyCallback(GLFWwindow*, int key, int, int action, int)
{
    int engineKey = GLFWToEngineKey(key);

    if (action == GLFW_PRESS)
    {
        s_EventQueue->Push<KeyPressedEvent>(engineKey);
    }
    else if (action == GLFW_RELEASE)
    {
        s_EventQueue->Push<KeyReleasedEvent>(engineKey);
    }
}

static void CursorPositionCallback(GLFWwindow*, double x, double y)
{
    s_EventQueue->Push<MouseMovedEvent>(x, y);
}

static void MouseButtonCallback(GLFWwindow*, int button, int action, int)
{
    int engineButton = ToMouseButton(button);


    if (action == GLFW_PRESS)
    {
        s_EventQueue->Push<MousePressedEvent>(engineButton);
    }
    else if (action == GLFW_RELEASE)
    {
        s_EventQueue->Push<MouseReleasedEvent>(engineButton);
    }
}

static void MouseScrollCallback(GLFWwindow*, double xoffset, double yoffset)
{
    s_EventQueue->Push<MouseScrolledEvent>(xoffset, yoffset);
}

namespace GLFWInputBridge
{
    void Attach(GLFWwindow* window, EventQueue* queue)
    {
        s_EventQueue = queue;

        glfwSetKeyCallback(window, KeyCallback);
        glfwSetCursorPosCallback(window, CursorPositionCallback);
        glfwSetMouseButtonCallback(window, MouseButtonCallback);
        glfwSetScrollCallback(window, MouseScrollCallback);
    }
}