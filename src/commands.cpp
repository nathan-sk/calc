#include "commands.h"
#include "calculator.h"

#include <iostream>
#include <string_view>
#include <cassert>

Command doCommand( std::string_view input )
{
    if ( input == "help" )
    {
        std::cout << "Welcome to Calc 1.0's help utility!"
                  << "\nCommands:\n"
                  << "- use `clear` to clear the terminal\n"
                  << "- use `help` to print the help utility\n"
                  << "- use `exit` or `quit` to quit the calculatrice\n"
                  << "\nOptions of the calculator:\n"
		  << "- Addition, subtraction, division, and multiplication operators\n"
		  << "- Modulo operator\n"
		  << "- operator priorities\n"
		  << "- Nested parentheses\n"
		  << "- functions : pi(), sqrt(), abs(), sin(), cos(), tan(), floor(), ceil(), and round()\n"
		  << "- Exponents (powers)\n";

        return command;
    }
    else if ( input == "clear" )
    {
        std::system("clear");//ne fonctionne que sous Linux
        return command;
    }
    else if ( input == "quit" || input == "exit" )
    {
        return quit;
    }
    else
    {
        return notCommand;
    }
}
