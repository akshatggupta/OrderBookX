#include "../include/orderbook.hpp"

int main() {

    OrderBook book;

    book.updateBid(100, 5);
    book.updateBid(101, 3);
    book.updateBid(102, 2);

    book.updateAsk(103, 1);
    book.updateAsk(104, 2);
    book.updateAsk(105, 4);

    book.printBook();

    return 0;
}