#pragma once

class Event;

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
}