#pragma once

#define EVENT_CLASS_TYPE(type)                  \
    static EventType GetStaticType()            \
    {                                           \
        return EventType::type;                 \
    }                                           \
                                                \
    EventType GetType() const override          \
    {                                           \
        return GetStaticType();                 \
    }                                           \
                                                \
    const char* GetName() const override        \
    {                                           \
        return #type;                           \
    }

#define EVENT_CLASS_CATEGORY(category)          \
    int GetCategoryFlags() const override       \
    {                                           \
        return category;                        \
    }

