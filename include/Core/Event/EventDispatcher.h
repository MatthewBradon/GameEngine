#pragma once

#include "Event.h"
#include <functional>

class EventDispatcher
{
    template<typename T>
    using EventFn = std::function<bool(T&)>;

public:
    EventDispatcher(Event& event)
        : m_Event(event) {}

    template<typename T>
    bool Dispatch(EventFn<T> func) {
        if (m_Event.GetType() == T::GetStaticType()) {
            m_Event.Handled = func(static_cast<T&>(m_Event));
            return true;
        }

        return false;
    }

private:
    Event& m_Event;
};