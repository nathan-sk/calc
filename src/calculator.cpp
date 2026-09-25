#include "calculator.h"
#include "utils.h"

#include <string>
#include <string_view>
#include <cmath>
#include <optional>

/*
 Tout le code utilise long double au lieu de double.
 Cela peut ête utile ou inutile en fonction des configurations.
*/

namespace calc
{
	class Operation
	{
	private:
		std::string m_result{};

		char m_symbol {};
		std::optional<long double> m_resultLeft {};
		std::optional<long double> m_resultRight {};

	public:
		std::string getResult() const { return m_result; }
		void setResult( std::string_view result ) { m_result = result; }

		char getSymbol() const { return m_symbol; }
		void setSymbol( char symbol ) { m_symbol = symbol; }

		std::optional<long double> getResultLeft() const { return m_resultLeft; }
		void setResultLeft( std::optional<long double> resultLeft ) { m_resultLeft = resultLeft; }

		std::optional<long double> getResultRight() const { return m_resultRight; }
		void setResultRight( std::optional<long double> resultRight ) { m_resultRight = resultRight; }
		
		std::optional<long double> doOperation()
		{
			switch (getSymbol())
			{
				case '+':
					return *getResultLeft() + *getResultRight();
				case '-':
					return *getResultLeft() - *getResultRight();
				case '*':
					return *getResultLeft() * *getResultRight();
				case '/':
					{
						if ( *getResultLeft() == 0 ) { return std::nullopt; }

						else { return *getResultLeft() / *getResultRight(); }
					}
				case '%':
					return std::fmod( *getResultLeft(), *getResultRight() );
				case '^':
					return pow( *getResultLeft(), *getResultRight() );
			}

			return 0;
		}

	std::optional<long double> sortOperation()
	{
		std::string calcul{ getResult() };

		for ( int x{ 0 }; x < 3; ++x )
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
					//définition du symbole
					setSymbol(calcul[i]);

					//définition du calcul de gauche
					setResult( std::string{ std::begin(calcul), std::begin(calcul) + i } );
					setResultLeft(sortOperation());

					//définition du calcul de droite
					setResult( std::string{ std::begin(calcul) + i + 1, std::end(calcul) } );
					setResultRight(sortOperation());

					//vérifie si le résultat correspond à une erreure
					if ( !getResultLeft() || !getResultRight() ) { return std::nullopt; }
					
					return  doOperation();
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
	};


	class Function
	{
	private:
		std::string m_name{};
		std::string m_calcul{};

		std::string m_result{};

	public:

		std::string getName() const { return m_name; }
		std::string getCalcul() const { return m_calcul; }
		std::string getResult() const { return m_result; }

		bool searchFunction( const std::string& calcul, std::string::iterator parenthesesBegin, std::string::iterator parenthesesEnd )
		{	
			if ( std::string{parenthesesBegin - 2, parenthesesBegin} == "pi" && parenthesesEnd == parenthesesBegin + 1 ) { m_name = "pi"; }
			else if ( std::string{parenthesesBegin - 4, parenthesesBegin} == "sqrt" )  { m_name = "sqrt"; }
			else if ( std::string{parenthesesBegin - 3, parenthesesBegin} == "abs" )   { m_name = "abs"; }
			else if ( std::string{parenthesesBegin - 3, parenthesesBegin} == "sin" )   { m_name = "sin"; }
			else if ( std::string{parenthesesBegin - 3, parenthesesBegin} == "cos" )   { m_name = "cos"; }
			else if ( std::string{parenthesesBegin - 3, parenthesesBegin} == "tan" )   { m_name = "tan"; }
			else if ( std::string{parenthesesBegin - 4, parenthesesBegin} == "asin" )  { m_name = "asin"; }
			else if ( std::string{parenthesesBegin - 4, parenthesesBegin} == "acos" )  { m_name = "acos"; }
			else if ( std::string{parenthesesBegin - 4, parenthesesBegin} == "atan" )  { m_name = "atan"; }
			else if ( std::string{parenthesesBegin - 5, parenthesesBegin} == "floor" ) { m_name = "floor"; }
			else if ( std::string{parenthesesBegin - 4, parenthesesBegin} == "ceil" )  { m_name = "ceil"; }
			else if ( std::string{parenthesesBegin - 5, parenthesesBegin} == "round" ) {m_name = "round"; }
			else { return false; }

			m_calcul = std::string{ parenthesesBegin + 1, parenthesesEnd };
			
			return true;
		}

		void doFunction()
		{
			if ( m_name == "pi" ) { m_result = std::to_string(M_PI); }
			else if ( m_name == "sqrt" )  { m_result = std::to_string( std::sqrt( *inputParser( m_calcul ) ) ); }
			else if ( m_name == "abs" )   { m_result = std::to_string( std::abs( *inputParser( m_calcul ) ) ); }
			else if ( m_name == "sin" )   { m_result = std::to_string( std::sin( *inputParser( m_calcul ) ) ); }
			else if ( m_name == "cos" )   { m_result = std::to_string( std::cos( *inputParser( m_calcul ) ) ); }
			else if ( m_name == "tan" )   { m_result = std::to_string( std::tan( *inputParser( m_calcul ) ) ); }
			else if ( m_name == "asin" )  { m_result = std::to_string( std::asin( *inputParser( m_calcul ) ) ); }
			else if ( m_name == "acos" )  { m_result = std::to_string( std::acos( *inputParser( m_calcul ) ) ); }
			else if ( m_name == "atan" )  { m_result = std::to_string( std::atan( *inputParser( m_calcul ) ) ); }
			else if ( m_name == "floor" ) { m_result = std::to_string( std::floor( *inputParser( m_calcul ) ) ); }
			else if ( m_name == "ceil" )  { m_result = std::to_string( std::ceil( *inputParser( m_calcul ) ) ); }
			else if ( m_name == "round" ) { m_result = std::to_string( std::round( *inputParser( m_calcul ) ) ); }
		}
	};

	std::optional<long double> inputParser( std::string calcul )
	{
		std::string parenthesesCalcul {calcul};

		int parenthesesCount {};
		std::string::iterator parenthesesBegin {};
		std::string::iterator parenthesesEnd {};

		Operation operation;
		operation.setResult(calcul);

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

					Function function;
					if ( function.searchFunction(calcul, parenthesesBegin, parenthesesEnd) )
					{	
						function.doFunction();
						calcul.replace( parenthesesBegin - static_cast<int>(std::size(function.getName())) 
								, parenthesesEnd + 1,  function.getResult() );
	
						it = std::begin(calcul);
						continue;
					}

					//appelle récusif de la fonction doParentheses jusqu'il n'y ai plus de parenthèses
					std::optional<long double> parenthesesResult { inputParser(std::string( parenthesesBegin + 1, parenthesesEnd )) };

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
		return operation.sortOperation();
	}
}
