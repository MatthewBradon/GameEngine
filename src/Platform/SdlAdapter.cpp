#include "Platform/SdlAdapter.h"

#include "Core/Log.h"
#include "Core/Event/EventQueue.h"
#include "Core/Event/EngineInput.h"
#include "Core/Event/KeyEvent.h"
#include "Core/Event/MouseEvent.h"
#include "Core/Event/WindowEvent.h"

#include <SDL3/SDL.h>

#include <iostream>

namespace
{
    int TranslateKeycode(SDL_Keycode keycode)
    {
        switch (keycode)
        {
            case SDLK_SPACE: return EngineInput::KEY_SPACE;
            case SDLK_APOSTROPHE: return EngineInput::KEY_APOSTROPHE;
            case SDLK_COMMA: return EngineInput::KEY_COMMA;
            case SDLK_MINUS: return EngineInput::KEY_MINUS;
            case SDLK_PERIOD: return EngineInput::KEY_PERIOD;
            case SDLK_SLASH: return EngineInput::KEY_SLASH;
            case SDLK_SEMICOLON: return EngineInput::KEY_SEMICOLON;
            case SDLK_EQUALS: return EngineInput::KEY_EQUAL;

            case SDLK_0: return EngineInput::KEY_0;
            case SDLK_1: return EngineInput::KEY_1;
            case SDLK_2: return EngineInput::KEY_2;
            case SDLK_3: return EngineInput::KEY_3;
            case SDLK_4: return EngineInput::KEY_4;
            case SDLK_5: return EngineInput::KEY_5;
            case SDLK_6: return EngineInput::KEY_6;
            case SDLK_7: return EngineInput::KEY_7;
            case SDLK_8: return EngineInput::KEY_8;
            case SDLK_9: return EngineInput::KEY_9;

            case SDLK_A: return EngineInput::KEY_A;
            case SDLK_B: return EngineInput::KEY_B;
            case SDLK_C: return EngineInput::KEY_C;
            case SDLK_D: return EngineInput::KEY_D;
            case SDLK_E: return EngineInput::KEY_E;
            case SDLK_F: return EngineInput::KEY_F;
            case SDLK_G: return EngineInput::KEY_G;
            case SDLK_H: return EngineInput::KEY_H;
            case SDLK_I: return EngineInput::KEY_I;
            case SDLK_J: return EngineInput::KEY_J;
            case SDLK_K: return EngineInput::KEY_K;
            case SDLK_L: return EngineInput::KEY_L;
            case SDLK_M: return EngineInput::KEY_M;
            case SDLK_N: return EngineInput::KEY_N;
            case SDLK_O: return EngineInput::KEY_O;
            case SDLK_P: return EngineInput::KEY_P;
            case SDLK_Q: return EngineInput::KEY_Q;
            case SDLK_R: return EngineInput::KEY_R;
            case SDLK_S: return EngineInput::KEY_S;
            case SDLK_T: return EngineInput::KEY_T;
            case SDLK_U: return EngineInput::KEY_U;
            case SDLK_V: return EngineInput::KEY_V;
            case SDLK_W: return EngineInput::KEY_W;
            case SDLK_X: return EngineInput::KEY_X;
            case SDLK_Y: return EngineInput::KEY_Y;
            case SDLK_Z: return EngineInput::KEY_Z;

            case SDLK_RETURN: return EngineInput::KEY_ENTER;
            case SDLK_TAB: return EngineInput::KEY_TAB;
            case SDLK_BACKSPACE: return EngineInput::KEY_BACKSPACE;
            case SDLK_INSERT: return EngineInput::KEY_INSERT;
            case SDLK_DELETE: return EngineInput::KEY_DELETE;
            case SDLK_RIGHT: return EngineInput::KEY_RIGHT;
            case SDLK_LEFT: return EngineInput::KEY_LEFT;
            case SDLK_DOWN: return EngineInput::KEY_DOWN;
            case SDLK_UP: return EngineInput::KEY_UP;
            case SDLK_PAGEUP: return EngineInput::KEY_PAGE_UP;
            case SDLK_PAGEDOWN: return EngineInput::KEY_PAGE_DOWN;
            case SDLK_HOME: return EngineInput::KEY_HOME;
            case SDLK_END: return EngineInput::KEY_END;
            case SDLK_CAPSLOCK: return EngineInput::KEY_CAPS_LOCK;

            case SDLK_LSHIFT: return EngineInput::KEY_LSHIFT;
            case SDLK_RSHIFT: return EngineInput::KEY_RSHIFT;
            case SDLK_LCTRL: return EngineInput::KEY_LCTRL;
            case SDLK_RCTRL: return EngineInput::KEY_RCTRL;
            case SDLK_LALT: return EngineInput::KEY_LALT;
            case SDLK_RALT: return EngineInput::KEY_RALT;

            case SDLK_LEFTBRACKET: return EngineInput::KEY_LEFT_BRACKET;
            case SDLK_BACKSLASH: return EngineInput::KEY_BACKSLASH;
            case SDLK_RIGHTBRACKET: return EngineInput::KEY_RIGHT_BRACKET;
            case SDLK_GRAVE: return EngineInput::KEY_GRAVEACCENT;

            case SDLK_ESCAPE: return EngineInput::KEY_ESCAPE;

            case SDLK_F1: return EngineInput::KEY_F1;
            case SDLK_F2: return EngineInput::KEY_F2;
            case SDLK_F3: return EngineInput::KEY_F3;
            case SDLK_F4: return EngineInput::KEY_F4;
            case SDLK_F5: return EngineInput::KEY_F5;
            case SDLK_F6: return EngineInput::KEY_F6;
            case SDLK_F7: return EngineInput::KEY_F7;
            case SDLK_F8: return EngineInput::KEY_F8;
            case SDLK_F9: return EngineInput::KEY_F9;
            case SDLK_F10: return EngineInput::KEY_F10;
            case SDLK_F11: return EngineInput::KEY_F11;
            case SDLK_F12: return EngineInput::KEY_F12;

            case SDLK_KP_0: return EngineInput::KEY_KP_0;
            case SDLK_KP_1: return EngineInput::KEY_KP_1;
            case SDLK_KP_2: return EngineInput::KEY_KP_2;
            case SDLK_KP_3: return EngineInput::KEY_KP_3;
            case SDLK_KP_4: return EngineInput::KEY_KP_4;
            case SDLK_KP_5: return EngineInput::KEY_KP_5;
            case SDLK_KP_6: return EngineInput::KEY_KP_6;
            case SDLK_KP_7: return EngineInput::KEY_KP_7;
            case SDLK_KP_8: return EngineInput::KEY_KP_8;
            case SDLK_KP_9: return EngineInput::KEY_KP_9;
            case SDLK_KP_DECIMAL: return EngineInput::KEY_KP_DECIMAL;
            case SDLK_KP_DIVIDE: return EngineInput::KEY_KP_DIVIDE;
            case SDLK_KP_MULTIPLY: return EngineInput::KEY_KP_MULTIPLY;
            case SDLK_KP_MINUS: return EngineInput::KEY_KP_SUBTRACT;
            case SDLK_KP_PLUS: return EngineInput::KEY_KP_ADD;
            case SDLK_KP_ENTER: return EngineInput::KEY_KP_ENTER;

            default: return EngineInput::UNKNOWN;
        }
    }

    int TranslateMouseButton(Uint8 button)
    {
        switch (button)
        {
            case SDL_BUTTON_LEFT: return EngineInput::MOUSE_LEFT;
            case SDL_BUTTON_RIGHT: return EngineInput::MOUSE_RIGHT;
            case SDL_BUTTON_MIDDLE: return EngineInput::MOUSE_MIDDLE;
            default: return EngineInput::UNKNOWN;
        }
    }
}

namespace SdlAdapter
{
    bool InitializeVideo()
    {
        return SDL_Init(SDL_INIT_VIDEO);
    }

    SDL_Window* CreateSDLWindow(const char* title, std::uint32_t width, std::uint32_t height)
    {
        return SDL_CreateWindow(title, static_cast<int>(width), static_cast<int>(height), SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);
    }

    void SetRelativeMouseMode(SDL_Window* window, bool enabled)
    {
        SDL_SetWindowRelativeMouseMode(window, enabled);
    }

    void PollEvents(EventQueue& eventQueue, bool& shouldClose, std::uint32_t& width, std::uint32_t& height)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                    eventQueue.Push<WindowCloseRequestedEvent>();
                    shouldClose = true;
                    break;

                case SDL_EVENT_WINDOW_RESIZED:
                    width = static_cast<std::uint32_t>(event.window.data1);
                    height = static_cast<std::uint32_t>(event.window.data2);
                    std::cout << "Window resized to: " << width << "x" << height << std::endl;
                    eventQueue.Push<WindowResizedEvent>(width, height);
                    break;

                case SDL_EVENT_KEY_DOWN:
                    if (!event.key.repeat) {
                        eventQueue.Push<KeyPressedEvent>(TranslateKeycode(event.key.key));
                    }
                    break;

                case SDL_EVENT_KEY_UP:
                    eventQueue.Push<KeyReleasedEvent>(TranslateKeycode(event.key.key));
                    break;

                case SDL_EVENT_MOUSE_MOTION:
                    eventQueue.Push<MouseMovedEvent>(event.motion.x, event.motion.y);
                    break;

                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                    eventQueue.Push<MousePressedEvent>(TranslateMouseButton(event.button.button));
                    break;

                case SDL_EVENT_MOUSE_BUTTON_UP:
                    eventQueue.Push<MouseReleasedEvent>(TranslateMouseButton(event.button.button));
                    break;

                case SDL_EVENT_MOUSE_WHEEL:
                    eventQueue.Push<MouseScrolledEvent>(event.wheel.x, event.wheel.y);
                    break;

                default:
                    break;
            }
        }
    }
}