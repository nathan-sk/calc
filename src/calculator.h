#include <string>

#ifndef CALCULATOR_H
#define CALCULATOR_H

namespace calc
{
	double doOperation( double number1, double number2, char symbol );
	double doCalcul( const std::string& calcul );
}

#endif
