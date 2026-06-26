#pragma once 
#include <string>
#include "event.hpp"

class Parser{
    public:
        Event parse(const std::string& line);

};

