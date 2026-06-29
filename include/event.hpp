#ifndef EVENT_HPP
#define EVENT_HPP

#include <string>
#include <chrono>

enum class EventType
{
    NEW_ORDER,
    TRADE_EXECUTED,
    BOOK_UPDATED,
    ORDER_CANCELLED,
    ORDER_MODIFIED
};

struct Event
{
    EventType type;

    std::string description;

    long long timestamp;

    Event(EventType t,
          const std::string &desc)
        : type(t),
          description(desc)
    {
        timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
                        std::chrono::system_clock::now().time_since_epoch())
                        .count();
    }
};

#endif

