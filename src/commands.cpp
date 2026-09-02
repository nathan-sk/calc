#include <iostream>
#include <string_view>

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
    else
    {
        return notCommand;
    }
}
