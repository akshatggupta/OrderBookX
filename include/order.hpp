#pragma once

#include <map>
#include <functional>
#include "event.hpp"

class OrderBook
{
private:
    std::map<double, double, std::greater<double>> bids;
    std::map<double, double> asks;

public:
    void updateBid(double price, double quantity);
    void updateAsk(double price, double quantity);

    void addOrder(Event event);

    void matchBuy(double price, double quantity);
    void matchSell(double price, double quantity);

    void printBook(int depth = 5);

    double bestBid();
    double bestAsk();
    double spread();
};