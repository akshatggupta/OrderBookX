#pragma once

#include <map>
#include <functional>
#include <cstddef>

#include "event.hpp"

class OrderBook
{
private:
    // Highest bid first
    std::map<double, double, std::greater<double>> bids;

    // Lowest ask first
    std::map<double, double> asks;

    // Internal helpers
    void updateBid(double price, double quantity);
    void updateAsk(double price, double quantity);

public:
    // Add a new order to the engine
    void addOrder(const Event &event);

    // Matching engine
    void matchBuy(double price, double quantity);
    void matchSell(double price, double quantity);

    // Market statistics
    double bestBid() const;
    double bestAsk() const;
    double spread() const;
    double midPrice() const;

    // Book information
    size_t bidLevels() const;
    size_t askLevels() const;

    // Display
    void printBook(int depth = 5) const;
};