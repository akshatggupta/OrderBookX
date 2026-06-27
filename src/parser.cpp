#include "../include/parser.hpp"
#include <sstream>
#include <stdexcept>

Event Parser::parse(const std::string& line)
{
    std::stringstream ss(line);
    double price;
    double quantity;

    ss>>side>>price>>quantity;


    Event event;
    if(side == "BUY"){
        event.side = Side::Buy;
    }
    else if(side == "SELL"){
        event.side = Side::Sell;

    }
    else{
        throw std::runtime_error("Invalid error");

    }
    event.price = price;
    event.quantity = quantity;

    return event;
}