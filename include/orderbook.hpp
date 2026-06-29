#pragma once

#include <map>
#include <vector>
#include <functional>
#include <utility>
#include <string>

#include "event.hpp"
#include "trade.hpp"
#include "eventlog.hpp"
#include "marketdata.hpp"

class OrderBook
{
private:

    // Highest bid first
    std::map<double, double, std::greater<double>> bids;

    // Lowest ask first
    std::map<double, double> asks;

    // Day 7 additions
    std::vector<Trade> tradeHistory;
    std::vector<EventLog> eventLogs;

    // Internal helpers
    void updateBid(double price, double quantity);
    void updateAsk(double price, double quantity);

    void recordTrade(double price,
                     double quantity);

    void recordEvent(EventType type,
                     const std::string &description);

public:

    // Matching Engine
    void addOrder(const Event &event);

    void matchBuy(double price,
                  double quantity);

    void matchSell(double price,
                   double quantity);

    // Market Information
    double bestBid() const;
    double bestAsk() const;
    double spread() const;
    double midPrice() const;

    size_t bidLevels() const;
    size_t askLevels() const;

    double totalBidVolume(int depth = 5) const;
    double totalAskVolume(int depth = 5) const;

    double imbalance(int depth = 5) const;

    double bidVWAP(int depth = 5) const;
    double askVWAP(int depth = 5) const;

    std::pair<double, double> largestBidOrder() const;
    std::pair<double, double> largestAskOrder() const;

    // Day 7 APIs
    MarketDataSnapshot getSnapshot() const;

    void printTradeHistory() const;
    void printEventLog() const;

    const std::vector<Trade>& getTradeHistory() const;
    const std::vector<EventLog>& getEventLogs() const;

    // Display
    void printBook(int depth = 5) const;
};