#include <string>
#include <optional>

#ifndef CALCULATOR_H
#define CALCULATOR_H

namespace calc
{
	struct Calcul 
	{
		char symbol {};
		std::optional<long double> resultLeft {};
		std::optional<long double> resultRight {};
		std::string calculLeft {};
		std::string calculRight {};
	};

	std::optional<long double> sortOperation( const std::string& calcul );
	std::optional<long double> inputParser( std::string calcul );
}

#endif
