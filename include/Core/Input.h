#pragma once

class Event;
class Window;

namespace Input
{
    void Update();

    void OnEvent(Event& event);

    bool IsKeyDown(int keycode);
    bool IsKeyPressed(int keycode);

    double GetMouseX();
    double GetMouseY();

    double GetMouseDeltaX();
    double GetMouseDeltaY();

    double GetScrollDeltaX();
    double GetScrollDeltaY();

    bool IsMouseButtonDown(int button);
    bool IsMouseButtonPressed(int button);

    bool SetWindow(Window* window);
}