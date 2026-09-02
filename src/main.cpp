#define DEBUG

#include "calculator.h"
#include "commands.h"
#include "utils.h"

#include <iostream>
#include <string>
#include <cassert>
#include <optional>

struct Version
{
    std::string name{"Calc"};
    std::string number{"1.0"};
    std::string versionName{"beta"};
    std::string date{"Aug 31 2026"};
    std::string gccVersion{"14.2.0"};
    std::string system{"linux"};
};

void welcome()
{
    //création d'une structure pour gérer les versions
    const Version calcVersion;
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

    welcome();

    //tests pour les calculs
    #ifdef DEBUG
    assert( calc::doCalcul( "2*2" ) == 4 );
    assert( calc::doCalcul( "2+2" ) == 4 );
    assert( calc::doCalcul( "2-2" ) == 0 );
    assert( calc::doCalcul( "2/2" ) == 1 );
    assert( calc::doCalcul( "2^3" ) == 8 );
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

        const std::optional<double> result = calc::doCalcul(input);
        const auto cmd = doCommand(input);

        //teste si l'entrée est une commande
        if ( cmd == command )
        {
            continue;
        }
        else if ( cmd == quit )
        {
            break;
        }


        //test si le résultat correspond à une erreure
        if (!result)
        {
            printError("incorrect entry");
        }
        else
        {
            std::cout << *result << '\n';
        }
    }

    return 0;
}
