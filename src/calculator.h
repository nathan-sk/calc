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

	std::optional<long double> doOperation( Calcul operationStruct );
	std::optional<long double> doCalcul( const std::string& calcul );
	std::optional<long double> sortCalcul( std::string calcul );
}

#endif
