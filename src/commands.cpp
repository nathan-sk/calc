#include "calculator.h"

#include <iostream>
#include <string_view>
#include <cassert>

enum Command
{
    command,
    notCommand,
    quit
};

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
                  << "- Basic operations and priorities work\n"
                  << "- Parenteses and functions also work\n";
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
    else if ( input == "debug" )
    {
        assert( calc::doCalcul( "2*2" ) == 4 );
        assert( calc::doCalcul( "2+2" ) == 4 );
        assert( calc::doCalcul( "2-2" ) == 0 );
        assert( calc::doCalcul( "2/2" ) == 1 );
        assert( calc::doCalcul( "2^3" ) == 8 );
        assert( calc::doCalcul( "2%2" ) == 0 );
        assert( calc::doCalcul( "2*2/2" ) == 2 );
        assert( calc::doCalcul( "2+2-2" ) == 2 );
        assert( calc::doCalcul( "2*2+2" ) == 6 );
        assert( calc::doCalcul( "2+2*2" ) == 6 );
        assert( calc::doCalcul( "2/2-2" ) == -1 );
        assert( calc::doCalcul( "2-2/2" ) == 1 );
        assert( calc::doCalcul( "2*2/2*2" ) == 4 );
        assert( calc::doCalcul( "2+2-2+2" ) == 4 );

        std::cout << "Calc works good!!!\n";
        return command;
    }
    else
    {
        return notCommand;
    }
}
