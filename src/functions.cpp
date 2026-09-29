#include "functions.h"
#include "calculator.h"

#include <string>
#include <math.h>

bool function::Function::find( const std::string& calcul, std::string::iterator parenthesesBegin, std::string::iterator parenthesesEnd )
{
	std::string functionCalcul{ std::string{ parenthesesBegin + 1, parenthesesEnd } };
	
	if ( std::string{parenthesesBegin - 2, parenthesesBegin} == "pi" && parenthesesEnd == parenthesesBegin + 1 )
	{
		setName("pi");
		setResult( std::to_string(M_PI) );
		return true;
	}

	if ( static_cast<int>( std::size(functionCalcul) ) <= 0 )
	{
		return false;
	}

	if ( std::string{parenthesesBegin - 4, parenthesesBegin} == "sqrt" )
	{
		setName("sqrt");
		setResult( std::to_string( std::sqrt( *calc::inputParser(functionCalcul) ) ) );
	}
	else if ( std::string{parenthesesBegin - 3, parenthesesBegin} == "abs" )
	{
		setName("abs");
		setResult( std::to_string( std::abs( *calc::inputParser(functionCalcul) ) ) );
	}
	else if ( std::string{parenthesesBegin - 3, parenthesesBegin} == "sin" )
	{
		setName("sin");
		setResult( std::to_string( std::sin( *calc::inputParser(functionCalcul) ) ) );
	}
	else if ( std::string{parenthesesBegin - 3, parenthesesBegin} == "cos" )
	{
		setName("cos");
		setResult( std::to_string( std::cos( *calc::inputParser(functionCalcul) ) ) );
	}
	else if ( std::string{parenthesesBegin - 3, parenthesesBegin} == "tan" )
	{
		setName("tan");
		setResult( std::to_string( std::tan( *calc::inputParser(functionCalcul) ) ) );
	}
	else if ( std::string{parenthesesBegin - 5, parenthesesBegin} == "floor" )
	{
		setName("floor");
		setResult( std::to_string( std::floor( *calc::inputParser(functionCalcul) ) ) );
	}
	else if ( std::string{parenthesesBegin - 4, parenthesesBegin} == "ceil" )
	{
		setName("ceil");
		setResult( std::to_string( std::ceil( *calc::inputParser(functionCalcul) ) ) );
	}
	else if ( std::string{parenthesesBegin - 5, parenthesesBegin} == "round" )
	{
		setName("round");
		setResult( std::to_string( std::round( *calc::inputParser(functionCalcul) ) ) );
	}
	else
	{
		return false;
	}

	return true;
}

