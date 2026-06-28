cmake_minimum_required(VERSION 3.20)
project(OrderBookX)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(
    orderbookx
    src/main.cpp
    src/orderbook.cpp
    src/parser.cpp
)