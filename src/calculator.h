#include <string>
#include <optional>
#include <iostream>

#ifndef CALCULATOR_H
#define CALCULATOR_H

namespace calc
{
	class Operation
	{
	public:
		std::string getResult() const { return m_result; }
		void setResult( std::string_view result ) { m_result = result; }

		std::optional<long double> getResultLeft() const { return m_resultLeft; }
		void setResultLeft( std::optional<long double> resultLeft ) { m_resultLeft = resultLeft; }

		std::optional<long double> getResultRight() const { return m_resultRight; }
		void setResultRight( std::optional<long double> resultRight ) { m_resultRight = resultRight; }
		
		std::optional<long double> doOperation(char symbol);

		std::optional<long double> sortOperation();

		Operation( std::string_view result ) 
			: m_result{ result }
		{
		}

	private:
		std::string m_result{};

		std::optional<long double> m_resultLeft {};
		std::optional<long double> m_resultRight {};
	};

	std::optional<long double> inputParser( std::string calcul );
}

#endif
