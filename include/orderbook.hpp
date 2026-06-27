#pragma  once
#include <map>
#include <functional>
#include "event.hpp"

enum Side {
    BUY,
    SELL
};

class Orderbook{
    private:
        std::map<double,int,std::greater<double>>bids;
        std::map<double,double> asks;
    public:
        void addOrder(Event event);
        void matchBuy(double price , double quantity);
        void matchSell(double price, double quantity);
        void printBook(int dept =5);
        


};

