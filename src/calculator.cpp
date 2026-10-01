#include "calculator.h"
#include "utils.h"
#include "functions.h"

#include <string>
#include <string_view>
#include <cmath>
#include <optional>

/*
Tout le code utilise long double au lieu de double.
Cela peut ête utile ou inutile en fonction des configurations.
*/

std::optional<long double> calc::Operation::doOperation(char symbol)
{
	switch (symbol)
	{
		case '+':
			return *getResultLeft() + *getResultRight();
		case '-':
			return *getResultLeft() - *getResultRight();
		case '*':
			return *getResultLeft() * *getResultRight();
		case '/':
			{
				if ( *getResultRight() == 0 ) { return std::nullopt; }

				else { return *getResultLeft() / *getResultRight(); }
			}
		case '%':
			return std::fmod( *getResultLeft(), *getResultRight() );
		case '^':
			return pow( *getResultLeft(), *getResultRight() );
	}

	return 0;
}

std::optional<long double> calc::Operation::sortOperation()
{
	std::string calcul{ getResult() };

	for ( int x{ 0 }; x < 3; ++x )
	{
		//cherche et réalise les additions et les soustractions en itérant depuis la fin
		for ( int i = static_cast<int>(std::size(calcul)) - 1; i >= 0; --i )
		{
			std::optional<char> symbol1{};
			std::optional<char> symbol2{};
			std::optional<char> symbol3{};

			if (x == 0) { symbol1 = '+'; symbol2 = '-'; symbol3 = std::nullopt; }
			if (x == 1) { symbol1 = '*'; symbol2 = '/'; symbol3 = '%'; }
			if (x == 2) { symbol1 = '^'; symbol2 = std::nullopt; symbol3 = std::nullopt; }

			if ( (calcul[i] == symbol1  || calcul[i] == symbol2 || calcul[i] == symbol3 ) && (i != 0) && (isdigit(calcul[i-1])) )
			{

				//définition du calcul de gauche
				setResult( std::string{ std::begin(calcul), std::begin(calcul) + i } );
				std::optional<long double> resultLeft = sortOperation();

				//définition du calcul de droite
				setResult( std::string{ std::begin(calcul) + i + 1, std::end(calcul) } );
				std::optional<long double> resultRight = sortOperation();

				setResultRight( resultRight );
				setResultLeft( resultLeft );
				//vérifie si le résultat correspond à une erreure
				if ( !getResultLeft() || !getResultRight() ) { return std::nullopt; }
			
				return  doOperation(calcul[i]);
			}
		}
	}

	if ( isDouble(calcul) )
	{
		//retourne le calcul convertit en nombre
		return stod(calcul);
	}
	else
	{
		//affecte la valeur d'erreur à result
		return std::nullopt;
	}
}

std::optional<long double> calc::inputParser( std::string calcul )
{
	std::string parenthesesCalcul {calcul};

	int parenthesesCount {};
	std::string::iterator parenthesesBegin {};
	std::string::iterator parenthesesEnd {};

	Operation operation{ calcul };

	for ( auto it = std::begin(calcul); it != std::end(calcul); ++it )
	{
		if ( *it == '(' )
		{	
			//vérifie si ce n'est pas une parenthèse imbriquée
			if ( parenthesesCount == 0 )
			{
				//affecte la valeur de l'itérateur it à parenthesesBegin
				parenthesesBegin = it;
			}

			++parenthesesCount;
		}
		else if ( *it == ')' )
		{
			--parenthesesCount;
			
			if ( parenthesesCount == 0 )
			{
				//affecte la valeur de l'itérateur it à parenthesesEnd
				parenthesesEnd = it;

				function::Function function;
				if ( function.find(calcul, parenthesesBegin, parenthesesEnd) )
				{	
					calcul.replace( parenthesesBegin - static_cast<int>(std::size(function.getName())) 
							, parenthesesEnd + 1,  function.getResult() );

					it = std::begin(calcul);
					operation.setResult(calcul);
					continue;
				}

				std::optional<long double> parenthesesResult { inputParser(std::string( parenthesesBegin + 1, parenthesesEnd )) };

				//vérifie si parenthesesResult renvoit une erreure(venant de doCalcul())
				if ( !parenthesesResult ) { return std::nullopt; };

				calcul.replace( parenthesesBegin, parenthesesEnd + 1, std::to_string(*parenthesesResult) );
				operation.setResult(calcul);

				it = std::begin(calcul);
			}
		}
	}

	//si la string ne contient pas de parenthèses, retourne le résultat du calcul
	return operation.sortOperation();
}
