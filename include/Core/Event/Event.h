#pragma once

#include <string>

enum class EventType
{
    None = 0,
    KeyPressed,
    KeyReleased,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseScrolled,
    WindowCloseRequested,
    WindowResized
};

class Event
{
public:
    virtual ~Event() = default;

    virtual EventType GetType() const = 0;
    virtual const char* GetName() const = 0;
    virtual int GetCategoryFlags() const = 0;
    
    bool IsInCategory(int category) {
        return GetCategoryFlags() & category;
    }


    bool Handled = false;
};


enum EventCategory
{
    EventCategoryNone        = 0,
    EventCategoryInput       = 1 << 0,
    EventCategoryKeyboard    = 1 << 1,
    EventCategoryMouse       = 1 << 2,
    EventCategoryMouseButton = 1 << 3,
    EventCategoryWindow      = 1 << 4
};