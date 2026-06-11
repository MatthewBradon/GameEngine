#pragma once

#include <string>

#include "Event.h"
#include "EventMacros.h"
#include "EngineInput.h"

class KeyEvent : public Event
{
public:
    int GetKeyCode() const
    {
        return m_KeyCode;
    }

    const char* GetKeyName() const
    {
        return EngineInput::ToString(m_KeyCode);
    }

    EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard)

protected:
    KeyEvent(int keycode)
        : m_KeyCode(keycode)
    {
    }

protected:
    int m_KeyCode;
};




class KeyPressedEvent : public KeyEvent
{
public:
    KeyPressedEvent(int keycode)
        : KeyEvent(keycode)
    {
    }

    EVENT_CLASS_TYPE(KeyPressed)
};




class KeyReleasedEvent : public KeyEvent
{
public:
    KeyReleasedEvent(int keycode)
        : KeyEvent(keycode)
    {
    }

    EVENT_CLASS_TYPE(KeyReleased)
};