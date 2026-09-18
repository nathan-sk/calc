#include <string>
#include <optional>
#include <stdfloat>

#ifndef CALCULATOR_H
#define CALCULATOR_H

namespace calc
{
	std::float128_t doOperation( std::float128_t number1, std::float128_t number2, char symbol );
	std::optional<std::float128_t> doCalcul( const std::string& calcul );
	std::optional<std::float128_t> doParentheses( std::string calcul );
}

#endif
