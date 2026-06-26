#pragma once 
#include <string>

enum class Sid{
    Buy,
    Sell
}

struct Event{
    Side side;
    double price;
    double quantity;
};


