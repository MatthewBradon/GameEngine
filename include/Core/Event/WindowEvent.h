#pragma once

#include <cstdint>

#include "Event.h"
#include "EventMacros.h"

class WindowCloseRequestedEvent : public Event
{
public:
    EVENT_CLASS_TYPE(WindowCloseRequested)
    EVENT_CLASS_CATEGORY(EventCategoryWindow)
};

class WindowResizedEvent : public Event
{
public:
    WindowResizedEvent(std::uint32_t width, std::uint32_t height)
        : m_Width(width), m_Height(height)
    {
    }

    std::uint32_t GetWidth() const
    {
        return m_Width;
    }

    std::uint32_t GetHeight() const
    {
        return m_Height;
    }

    EVENT_CLASS_TYPE(WindowResized)
    EVENT_CLASS_CATEGORY(EventCategoryWindow)

private:
    std::uint32_t m_Width;
    std::uint32_t m_Height;
};