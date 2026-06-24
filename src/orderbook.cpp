#include "../include/orderbook.hpp"
#include <iostream>

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
