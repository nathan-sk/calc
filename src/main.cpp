#define DEBUG

#include "calculator.h"
#include "commands.h"
#include "utils.h"

#include <iostream>
#include <string>
#include <cassert>
#include <limits>

struct Version
{
    std::string name{};
    float number {};
    std::string versionName {};
    std::string date {};
    std::string gccVersion {};
    std::string system {};
};

void welcome()
{
    //création d'une structure pour gérer les versions
    Version calcVersion{ "Calc", 1.0, "beta", "Aug 31 2026", "14.2.0", "linux" };
    std::cout << calcVersion.name << ' '
              << calcVersion.number << " ("
              << calcVersion.versionName << ", "
              << calcVersion.date << ") [GCC "
              << calcVersion.gccVersion << "] on "
              << calcVersion.system << '\n'
              << "Type \"help\" for more information.\n";
}

int main()
{
    std::string input {};
    double result {};

    welcome();

    //tests pour les calculs
    #ifdef DEBUG
    assert( calc::doCalcul( "2*2" ) == 4 );
    assert( calc::doCalcul( "2+2" ) == 4 );
    assert( calc::doCalcul( "2-2" ) == 0 );
    assert( calc::doCalcul( "2/2" ) == 1 );
    assert( calc::doCalcul( "2*2/2" ) == 2 );
    assert( calc::doCalcul( "2+2-2" ) == 2 );
    assert( calc::doCalcul( "2*2+2" ) == 6 );
    assert( calc::doCalcul( "2+2*2" ) == 6 );
    assert( calc::doCalcul( "2/2-2" ) == -1 );
    assert( calc::doCalcul( "2-2/2" ) == 1 );
    assert( calc::doCalcul( "2*2/2*2" ) == 4 );
    assert( calc::doCalcul( "2+2-2+2" ) == 4 );
    #endif

    while(true)
    {
        //affiche le prompt
        std::cout << "\033[95m>>> \033[0m";
        getline(std::cin, input);

        //teste si l'entrée est une commande
        if ( doCommand(input) == command )
        {
            continue;
        }
        else if ( doCommand(input) == quit )
        {
            return 0;
        }
        else
        {
            result = calc::doCalcul(input);
        }

        //test si le résult correspond à une erreure
        if ( result == std::numeric_limits<double>::max() )
        {
            printError("incorrect entry");
        }
        else
        {
            std::cout << result << '\n';
        }
    }

    return 0;
}
