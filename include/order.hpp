#pragma  once
#include <map>
#include <functional>

enum class side{
    BID,
    ASK
};

struct Order{
    double price;
    double quantity;
    side side;

};

class Orderbook{
    public:
        void updatebit(double price, double quantity);
        void updateAsk(double price, double quantity);
        void printBook() const;

    private:
        std::map<double, double, std::greater<double>> bids;
        std::map<double,double>;

};
