#include "utils.h"

#include <iostream>
#include <string>

bool isDouble( const std::string& string )
{
    try
    {
        std::stod(string);
    }
    catch(...)
    {
        return false;
    }

    return true;
}

void printError( const std::string& error )
{
    std::cout << "\033[31merror: " << error <<"\033[0m\n";
}
