#include "../include/orderbook.hpp"
#include <iostream>
#include <algorithm>
#include<iostream>

void OrderBook::updateBid(double price, double quantity){
    if (quantity == 0){
        bids.erase(price);
    }
    else{
        bids[price] = quantity;
    }
}


void OrderBook::updateAsk(double price, double quantity){
    if(quantity == 0){
        asks.erase(price);

    }
    else{
        asks[price] = quantity;
    }
}

void OrderBook:: printBook()const{
    std::cout << "\nASKS\n";

    for (const auto& [price, quantity] : asks) {
        std::cout << price << " : " << quantity << '\n';
    }

    std::cout << "-----------------\n";

    std::cout << "BIDS\n";

    for (const auto& [price, quantity] : bids) {
        std::cout << price << " : " << quantity << '\n';
    }
}


void OrderBook:: matchBuy(double price, int quatity){
    while (
        quantity >0 &&
        !asks.empty()&&
        asks.begin()-> first <= price
    )

    {
        auto bestAsk = asks.begin();
        int tradeQty = std::min(quantity, bestAsk->second);

        std::cout << "TRADE"
                  << tradeQty
                  << "@"
                  <<bestAsk->first
                  <<std::endl;

        quantity -= tradeQty;
        bestAsk->second -= tradeQty;
        if (bestAsk->second==0){
            asks.erase(bestAsk);

        }

    }
    if (quantity>0){
        bids[price]+=quantity;
    }
}


void OrderBook:: matchSell(double price , int quantity){
    while(
        quantity >0 &&
        !bids.empty() &&
        bids.begin()-> first >=price
    )

    {
        auto bestBid = bids.begin();
        int tradeQty = std::min(quantity, bestbid->second);


        std::cout <<"TRADE"
                  << tradeQty
                  << "@"
                  <<bestbid->first
                  <<std::endl;

        quantity -= tradeQty;
        bestBid->second -= tradeQty;
        if (bestBid->second==0){
            bids.erase(bestBid);

        }

    }
    if (quantity>0){
        asks[price] += quantity;
    }
    }



void OrderBook::addOrder(Side side, double price, int quantity)
{
    if (side == BUY)
    {
        matchBuy(price, quantity);
    }
    else
    {
        matchSell(price, quantity);
    }
}


void OrderBook::printBook() const
{
    std::cout << "\n========== ORDER BOOK ==========\n";

    std::cout << "\nASKS\n";
    for (const auto &[price, quantity] : asks)
    {
        std::cout << price << " : " << quantity << '\n';
    }

    std::cout << "\n-------------------------------\n";

    std::cout << "\nBIDS\n";
    for (const auto &[price, quantity] : bids)
    {
        std::cout << price << " : " << quantity << '\n';
    }

    std::cout << "================================\n";
}
