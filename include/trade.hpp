#pragma once

#include <chrono>

struct Trade
{
    double price;
    double quantity;
    long long timestamp;

    Trade(double p, double q)
        : price(p),
          quantity(q)
    {
        timestamp =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch())
                .count();
    }
};