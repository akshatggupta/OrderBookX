#pragma once

#include <map>
#include <functional>
#include <utility>

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
    // Matching Engine
    void addOrder(const Event &event);

    void matchBuy(double price, double quantity);
    void matchSell(double price, double quantity);

    // Basic Market Information
    double bestBid() const;
    double bestAsk() const;
    double spread() const;
    double midPrice() const;

    size_t bidLevels() const;
    size_t askLevels() const;

    // ---------- Day 6 Analytics ----------

    // Total quantity available
    double totalBidVolume(int depth = 5) const;
    double totalAskVolume(int depth = 5) const;

    // Order Book Imbalance
    double imbalance(int depth = 5) const;

    // Volume Weighted Average Price
    double bidVWAP(int depth = 5) const;
    double askVWAP(int depth = 5) const;

    // Largest resting orders
    std::pair<double, double> largestBidOrder() const;
    std::pair<double, double> largestAskOrder() const;

    // Display
    void printBook(int depth = 5) const;
};