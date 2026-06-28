#pragma once

#include <map>
#include <functional>

#include "event.hpp"

class OrderBook
{
private:
    // Highest bid first
    std::map<double, double, std::greater<double>> bids;

    // Lowest ask first
    std::map<double, double> asks;

    void updateBid(double price, double quantity);
    void updateAsk(double price, double quantity);

public:
    void addOrder(const Event &event);

    void matchBuy(double price, double quantity);
    void matchSell(double price, double quantity);

    void printBook(int depth = 5);

    double bestBid();
    double bestAsk();
    double spread();
};