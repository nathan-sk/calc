#include "calculator.h"
#include "utils.h"

#include <string>
#include <cmath>
#include <optional>

/*
 Tout le code utilise long double au lieu de double.
 Cela peut ête utile ou inutile en fonction des configurations.
*/

namespace calc
{
	std::optional<long double> doOperation( Calcul operationStruct )
	{
		switch (operationStruct.symbol)
		{
			case '+':
				return *operationStruct.resultLeft + *operationStruct.resultRight;
			case '-':
				return *operationStruct.resultLeft - *operationStruct.resultRight;
			case '*':
				return *operationStruct.resultLeft * *operationStruct.resultRight;
			case '/':
				{
					if ( *operationStruct.resultRight == 0 )
					{
						return std::nullopt;
					}
					else
					{
						return *operationStruct.resultLeft / *operationStruct.resultRight;
					}
				}
			case '%':
				return std::fmod(*operationStruct.resultLeft, *operationStruct.resultRight);
			case '^':
				return pow( *operationStruct.resultLeft, *operationStruct.resultRight );
		}

		return 0;
	}

	std::optional<long double> doCalcul( const std::string& calcul )
	{
		for(int x{0}; x < 3; ++x)
		{
			//cherche et réalise les additions et les soustractions en itérant depuis la fin
			for ( int i = std::size(calcul) - 1; i >= 0; --i )
			{
				std::optional<char> symbol1{};
				std::optional<char> symbol2{};
				std::optional<char> symbol3{};

				if (x == 0) { symbol1 = '+'; symbol2 = '-'; symbol3 = std::nullopt; }
				if (x == 1) { symbol1 = '*'; symbol2 = '/'; symbol3 = '%'; }
				if (x == 2) { symbol1 = '^'; symbol2 = std::nullopt; symbol3 = std::nullopt; }

				if ( (calcul[i] == symbol1  || calcul[i] == symbol2 || calcul[i] == symbol3 ) && (i != 0) && (isdigit(calcul[i-1])) )
				{
					Calcul calculStruct;

					//définition du symbole
					calculStruct.symbol = calcul[i];

					//définition du calcul de gauche
					calculStruct.calculLeft = { std::begin(calcul), std::begin(calcul) + i };
					calculStruct.resultLeft = doCalcul(calculStruct.calculLeft);

					//définition du calcul de droite
					calculStruct.calculRight = { std::begin(calcul) + i + 1, std::end(calcul) };
					calculStruct.resultRight = doCalcul(calculStruct.calculRight);

					//vérifie si le résultat correspond à une erreure
					if ( !calculStruct.resultLeft || !calculStruct.resultRight ) { return std::nullopt; }

					return  doOperation( calculStruct );
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

	std::optional<long double> sortCalcul( std::string calcul )
	{
		std::string parenthesesCalcul {calcul};

		int parenthesesCount {};
		std::string::iterator parenthesesBegin {};
		std::string::iterator parenthesesEnd {};

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
				
				//vérfie si la parenthèse est terminée
				if ( parenthesesCount == 0 )
				{
					//affecte la valeur de l'itérateur it à parenthesesEnd
					parenthesesEnd = it;

					if(std::string{parenthesesBegin - 2, parenthesesBegin} == "pi" && parenthesesEnd == parenthesesBegin + 1)
					{
						calcul.replace( parenthesesBegin - 2, parenthesesEnd + 1, std::to_string(M_PI) );
						it = std::begin(calcul);
						continue;
					}
					else if(std::string{parenthesesBegin - 4, parenthesesBegin} == "sqrt" && parenthesesEnd != parenthesesBegin + 1 )
					{
						calcul.replace( parenthesesBegin - 4, parenthesesEnd + 1, std::to_string( std::sqrt( *sortCalcul(std::string( parenthesesBegin + 1, parenthesesEnd)) ) ) );
						it = std::begin(calcul);
						continue;
					}

					//appelle récusif de la fonction doParentheses jusqu'il n'y ai plus de parenthèses
					std::optional<long double> parenthesesResult { sortCalcul(std::string( parenthesesBegin + 1, parenthesesEnd )) };

					//vérifie si parenthesesResult renvoit une erreure(venant de doCalcul())
					if ( !parenthesesResult ) { return std::nullopt; };

					//remplace le texte de parenthesesBegin à parenthesesEnd par le parenthesesResult
					calcul.replace( parenthesesBegin, parenthesesEnd + 1, std::to_string(*parenthesesResult) );

					//réinitialise la position de it
					it = std::begin(calcul);
				}
			}
		}

		//si la string ne contient pas de parenthèses, retourne le résultat du calcul
		return doCalcul(calcul);
	}
}
