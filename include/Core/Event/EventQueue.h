#pragma once

#include <memory>
#include <vector>

#include "Event.h"

class EventQueue
{
public:
    template<typename T, typename... Args>
    void Push(Args&&... args) {
        m_Events.push_back(
            std::make_unique<T>(std::forward<Args>(args)...)
        );
    }

    std::vector<std::unique_ptr<Event>>& GetEvents() {
        return m_Events;
    }

    void Clear() {
        m_Events.clear();
    }

private:
    std::vector<std::unique_ptr<Event>> m_Events;
};