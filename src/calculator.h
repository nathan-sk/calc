#include <string>
#include <optional>

#ifndef CALCULATOR_H
#define CALCULATOR_H

namespace calc
{
	double doOperation( double number1, double number2, char symbol );
	std::optional<double> doCalcul( const std::string& calcul );
}

#endif
