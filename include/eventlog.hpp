#pragma once

#include <string>
#include <chrono>

enum class EventType
{
    NEW_ORDER,
    TRADE_EXECUTED,
    BOOK_UPDATED
};

struct EventLog
{
    EventType type;
    std::string description;
    long long timestamp;

    EventLog(EventType t,
             const std::string &desc)
        : type(t),
          description(desc)
    {
        timestamp =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch())
                .count();
    }
};