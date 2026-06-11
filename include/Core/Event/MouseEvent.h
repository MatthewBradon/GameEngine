#pragma once

#include "Event.h"
#include "EventMacros.h"
#include "EngineInput.h"

class MouseMovedEvent : public Event
{
public:
    MouseMovedEvent(double x, double y)
        : m_MouseX(x), m_MouseY(y)
    {
    }

    double GetX() const
    {
        return m_MouseX;
    }

    double GetY() const
    {
        return m_MouseY;
    }

    EVENT_CLASS_TYPE(MouseMoved)
    EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)

private:
    double m_MouseX;
    double m_MouseY;
};

class MousePressedEvent : public Event
{
public:
    MousePressedEvent(int button)
        : m_Button(button)
    {
    }

    int GetButton() const
    {
        return m_Button;
    }

    const char* GetButtonName() const
    {
        return EngineInput::ToString(m_Button);
    }

    EVENT_CLASS_TYPE(MouseButtonPressed)
    EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouseButton)
private:
    int m_Button;
};

class MouseReleasedEvent : public Event
{
public:
    MouseReleasedEvent(int button)
        : m_Button(button)
    {
    }

    int GetButton() const
    {
        return m_Button;
    }

    const char* GetButtonName() const
    {
        return EngineInput::ToString(m_Button);
    }

    EVENT_CLASS_TYPE(MouseButtonReleased)
    EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouseButton)
private:
    int m_Button;
};

class MouseScrolledEvent : public Event
{
public:
    MouseScrolledEvent(double xOffset, double yOffset)
        : m_XOffset(xOffset), m_YOffset(yOffset)
    {
    }

    double GetXOffset() const
    {
        return m_XOffset;
    }

    double GetYOffset() const
    {
        return m_YOffset;
    }

    EVENT_CLASS_TYPE(MouseScrolled)
    EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
private:
    double m_XOffset;
    double m_YOffset;
};