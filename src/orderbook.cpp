#include "../include/orderbook.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <stdexcept>

void OrderBook::updateBid(double price, double quantity)
{
    if (quantity == 0)
        bids.erase(price);
    else
        bids[price] = quantity;
}

void OrderBook::updateAsk(double price, double quantity)
{
    if (quantity == 0)
        asks.erase(price);
    else
        asks[price] = quantity;
}

void OrderBook::matchBuy(double price, double quantity)
{
    while (quantity > 0 &&
           !asks.empty() &&
           asks.begin()->first <= price)
    {
        auto bestAsk = asks.begin();

        double tradeQty = std::min(quantity, bestAsk->second);

        std::cout << "TRADE "
                  << tradeQty
                  << " @ "
                  << bestAsk->first
                  << '\n';

        quantity -= tradeQty;
        bestAsk->second -= tradeQty;

        if (bestAsk->second == 0)
            asks.erase(bestAsk);
    }

    if (quantity > 0)
    {
        updateBid(price, bids[price] + quantity);
    }
}

void OrderBook::matchSell(double price, double quantity)
{
    while (quantity > 0 &&
           !bids.empty() &&
           bids.begin()->first >= price)
    {
        auto bestBid = bids.begin();

        double tradeQty = std::min(quantity, bestBid->second);

        std::cout << "TRADE "
                  << tradeQty
                  << " @ "
                  << bestBid->first
                  << '\n';

        quantity -= tradeQty;
        bestBid->second -= tradeQty;

        if (bestBid->second == 0)
            bids.erase(bestBid);
    }

    if (quantity > 0)
    {
        updateAsk(price, asks[price] + quantity);
    }
}

void OrderBook::addOrder(const Event &event)
{
    if (event.side == Side::Buy)
        matchBuy(event.price, event.quantity);
    else
        matchSell(event.price, event.quantity);
}

double OrderBook::bestBid() const
{
    if (bids.empty())
        throw std::runtime_error("No bids in book");

    return bids.begin()->first;
}

double OrderBook::bestAsk() const
{
    if (asks.empty())
        throw std::runtime_error("No asks in book");

    return asks.begin()->first;
}

double OrderBook::spread() const
{
    return bestAsk() - bestBid();
}

double OrderBook::midPrice() const
{
    return (bestBid() + bestAsk()) / 2.0;
}

size_t OrderBook::bidLevels() const
{
    return bids.size();
}

size_t OrderBook::askLevels() const
{
    return asks.size();
}

void OrderBook::printBook(int depth) const
{
    using std::cout;
    using std::fixed;
    using std::left;
    using std::right;
    using std::setprecision;
    using std::setw;

    cout << "\n==================================================\n";
    cout << "                  ORDER BOOK\n";
    cout << "==================================================\n\n";

    try
    {
        cout << fixed << setprecision(2);

        cout << "Best Bid   : " << bestBid() << '\n';
        cout << "Best Ask   : " << bestAsk() << '\n';
        cout << "Spread     : " << spread() << '\n';
        cout << "Mid Price  : " << midPrice() << '\n';
    }
    catch (const std::runtime_error &)
    {
        cout << "Book is not fully populated yet.\n";
    }

    cout << "Bid Levels : " << bidLevels() << '\n';
    cout << "Ask Levels : " << askLevels() << "\n\n";

    cout << "-------------------- ASKS --------------------\n";
    cout << left << setw(15) << "Price"
         << setw(15) << "Quantity" << '\n';

    cout << "----------------------------------------------\n";

    int count = 0;

    for (const auto &ask : asks)
    {
        if (count >= depth)
            break;

        cout << right
             << setw(15) << ask.first
             << setw(15) << ask.second
             << '\n';

        count++;
    }

    cout << "\n-------------------- BIDS --------------------\n";
    cout << left << setw(15) << "Price"
         << setw(15) << "Quantity" << '\n';

    cout << "----------------------------------------------\n";

    count = 0;

    for (const auto &bid : bids)
    {
        if (count >= depth)
            break;

        cout << right
             << setw(15) << bid.first
             << setw(15) << bid.second
             << '\n';

        count++;
    }

    cout << "==================================================\n";
}

double OrderBook::totalBidVolume(int depth) const
{
    double totalVolume = 0.0;
    int count = 0;

    for (const auto &bid : bids)
    {
        if (count >= depth)
            break;

        totalVolume += bid.second;
        count++;
    }

    return totalVolume;
}

double OrderBook::totalAskVolume(int depth) const
{
    double totalVolume = 0.0;
    int count = 0;

    for (const auto &ask : asks)
    {
        if (count >= depth)
            break;

        totalVolume += ask.second;
        count++;
    }

    return totalVolume;
}

double OrderBook::imbalance(int depth) const
{
    double bidVolume = totalBidVolume(depth);
    double askVolume = totalAskVolume(depth);

    double totalVolume = bidVolume + askVolume;

    if (totalVolume == 0.0)
    {
        return 0.0;
    }

    return (bidVolume - askVolume) / totalVolume;
}

double OrderBook:: askVWAP(int depth) const{
    double weightedPrice = 0.0;
    double totalVolume = 0.0;
    int count = 0.0;

    int count = 0;

    for (const auto &ask : asks)
    {
        if (count >= depth)
            break;

        weightedPrice += ask.first * ask.second;
        totalVolume += ask.second;

        count++;
    }

    if (totalVolume == 0.0)
        return 0.0;

    return weightedPrice / totalVolume;
}

std::pair<double, double> OrderBook::largestBidOrder() const
{
    if (bids.empty())
        return {0.0, 0.0};

    auto largest = bids.begin();

    for (auto it = bids.begin(); it != bids.end(); ++it)
    {
        if (it->second > largest->second)
            largest = it;
    }

    return {largest->first, largest->second};
}

std::pair<double, double> OrderBook::largestAskOrder() const
{
    if (asks.empty())
        return {0.0, 0.0};

    auto largest = asks.begin();

    for (auto it = asks.begin(); it != asks.end(); ++it)
    {
        if (it->second > largest->second)
            largest = it;
    }

    return {largest->first, largest->second};
}