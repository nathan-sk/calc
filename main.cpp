#define DEBUG

#include <iostream>
#include <string>
#include <string_view>
#include <cassert>
#include <limits>

enum Command
{
	command,
	notCommand,
	quit,
};

bool isdouble( const std::string& string )
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
	std::cout << "\033[31merror: " << error << "\033[0m\n";
}

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
			  << "- Parenteses also work\n";
		return command;
	}
	else if ( input == "clear" )
	{
		std::system("clear");
		return command;
	}
	else if ( input == "exit" || input == "quit" )
	{
		return quit;
	}
	else
	{
		return notCommand;
	}
}

namespace calc
{
	double doOperation( double number1, double number2, char symbol )
	{
		double result{};

		switch ( symbol )
			{
			case '+':
				result = number1 + number2;
				break;
			case '-':
				result = number1 - number2;
				break;
			case '*':
				result = number1 * number2;
				break;
			case '/':
				result = number1 / number2;
				break;
			}

		return result;
	}

		

	double doCalcul( const std::string& calcul )
	{
		std::string calculRight{};
		std::string calculLeft{};

		double resultRight{};
		double resultLeft{};

		double result{};

		for ( int i = std::size(calcul) - 1; i >= 0; --i )
		{
			if (  calcul[i] == '+' || calcul[i] == '-' )
			{
				calculRight = { std::begin(calcul), std::begin(calcul) + i };
				resultRight = doCalcul( calculRight );

				calculLeft = { std::begin(calcul) + i + 1, std::end(calcul) };
				resultLeft = doCalcul( calculLeft );

				if ( resultRight == std::numeric_limits<double>::max() || resultLeft == std::numeric_limits<double>::max() ) 
				{
					return result = std::numeric_limits<double>::max();
				}


				result = doOperation( resultRight, resultLeft, calcul[i] );
				
				return result;
			}
		}
		
		for ( int i = std::size(calcul) - 1; i >= 0; --i )
		{
			if ( calcul[i] == '*' || calcul[i] == '/' )
			{
				calculRight = { std::begin(calcul), std::begin(calcul) + i };
				resultRight = doCalcul( calculRight );
			
				calculLeft = { std::begin(calcul) + i + 1, std::end(calcul) };
				resultLeft = doCalcul( calculLeft );

				if ( resultRight == std::numeric_limits<double>::max() || resultLeft == std::numeric_limits<double>::max() ) 
				{
					return result = std::numeric_limits<double>::max();
				}

				result = doOperation( resultRight, resultLeft, calcul[i] );

				return result;
			}
			else
			{
				if ( isdouble(calcul) )
				{
					result = stod(calcul);
				}
				else
				{
					result = std::numeric_limits<double>::max();
				}
			}
		}
		
		return result;
	}
}

int main()
{
	std::string input{};

	double result{};

	std::cout << "Calc 1.0 (alpha, Aug 27 2026) [GCC 14.2.0] on linux\n"
		  << "Type \"help\" for more information.\n";
		
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

	
	while( true )
	{
		std::cout << "\033[95m>>> \033[0m";
		getline(std::cin, input);

		if ( doCommand( input ) == command )
		{
			continue;
		}
		else if ( doCommand( input ) == quit )
		{
			return 0;
		}
		
		result = calc::doCalcul( input );

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
