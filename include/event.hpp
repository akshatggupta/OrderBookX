#pragma once 
#include <string>

enum class Side{
    Buy,
    Sell
};

struct Event{
    Side side;
    double price;
    double quantity;
};


