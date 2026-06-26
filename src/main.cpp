#include <iostream>
#include <string>

#include "../include/parser.hpp"
#include "../include/orderbook.hpp"

int main()
{
    Parser parser;
    OrderBook book;

    std::string line;

    std::cout << "===== OrderBookX =====" << std::endl;
    std::cout << "Enter orders in the format:" << std::endl;
    std::cout << "BUY 100 5" << std::endl;
    std::cout << "SELL 101 3" << std::endl;
    std::cout << "Type EXIT to quit.\n" << std::endl;

    while (true)
    {
        std::cout << "> ";

        std::getline(std::cin, line);

        if (line == "EXIT")
            break;

        try
        {
            Event event = parser.parse(line);

            book.addOrder(event);

            std::cout << "\nUpdated Order Book\n";
            book.printBook();
            std::cout << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cout << "Error : " << e.what() << std::endl;
        }
    }

    std::cout << "Program terminated." << std::endl;

    return 0;
}