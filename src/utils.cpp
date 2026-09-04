#include "utils.h"

#include <iostream>
#include <string>

bool isDouble( const std::string& string )
{
    if ( std::size(string) == 0 )
    {
        return false;
    }

    int countPoint{0};

    for ( int i = 0; i < std::size(string); ++i )
    {
        if ( !isdigit(string[i]) && string[i] != '-' && string[i] != '.' )
        {
            return false;
        }
        else if ( string[i] == '.' )
        {
            ++countPoint;

            if (countPoint > 1 || i == 0)
            {
                return false;
            }
        }
        else if ( string[i] == '-' && i != 0)
        {
            return false;
        }
    }

    return true;
}

void printError( const std::string& error )
{
    std::cout << "\033[31merror: " << error <<"\033[0m\n";
}
