#include "../include/orderbook.hpp"

#include <iostream>
#include <algorithm>
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

void OrderBook::printBook(int depth)
{
    std::cout << "\n========== ORDER BOOK ==========\n";

    std::cout << "\nASKS\n";

    int count = 0;

    for (const auto &ask : asks)
    {
        if (count == depth)
            break;

        std::cout << ask.first << " -> " << ask.second << '\n';
        count++;
    }

    std::cout << "\n---------------------------\n";

    std::cout << "\nBIDS\n";

    count = 0;

    for (const auto &bid : bids)
    {
        if (count == depth)
            break;

        std::cout << bid.first << " -> " << bid.second << '\n';
        count++;
    }

    std::cout << "===============================\n";
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

void OrderBook::addOrder(Event event)
{
    if (event.side == Side::Buy)
    {
        matchBuy(event.price, event.quantity);
    }
    else
    {
        matchSell(event.price, event.quantity);
    }
}

double OrderBook::bestBid()
{
    if (bids.empty())
    {
        throw std::runtime_error("No bids in book");
    }

    return bids.begin()->first;
}


double OrderBook::bestAsk()
{
    if (asks.empty())
    {
        throw std::runtime_error("No asks in book");
    }

    return asks.begin()->first;
}


double OrderBook::spread()
{
    return bestAsk() - bestBid();
}