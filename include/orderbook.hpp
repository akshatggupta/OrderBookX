#pragma  once
#include <map>
#include <functional>

enum Side {
    BUY,
    SELL
};

class Orderbook{
    private:
        std::map<double,int,std::greater<double>>bids;
        std::map<double,int> asks;
    public:
        void addOrder(Side side, double price, int quantity);
        void matchBuy(double price , double quantity);
        void matchSell(double price, double quantity);
        void printBook();


};

