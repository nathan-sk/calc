#include "calculator.h"
#include "utils.h"

#include <string>
#include <limits>

namespace calc
{
    double doOperation( double number1, double number2, char symbol )
    {
        double result {};

        switch (symbol)
        {
            case '+':
                result = number1 + number2;
                break;
            case '-':
                result = number1 - number2;
                break;
            case '*':
                result = number1 * number2;
                break;
            case '/':
            {
                result = number1 / number2;
                break;
            }
        }

        return result;
    }

    double doCalcul( const std::string& calcul )
    {
        std::string calculLeft {};
        std::string calculRight {};
        double resultLeft {};
        double resultRight {};
        double result {};

        //cherche et réalise les additions et les soustractions en itérant depuis la fin
        for ( int i = std::size(calcul) - 1; i >= 0; --i )
        {
            if ( calcul[i] == '+' || calcul[i] == '-' )
            {
                calculLeft = { std::begin(calcul), std::begin(calcul) + i };
                resultLeft = doCalcul(calculLeft);

                calculRight = { std::begin(calcul) + i + 1, std::end(calcul) };
                resultRight = doCalcul(calculRight);

                //vérifie si le résultat correspond à une erreure
                if ( resultLeft == std::numeric_limits<double>::max() || resultRight == std::numeric_limits<double>::max() )
                {
                    return result = std::numeric_limits<double>::max();
                }

                result = doOperation( resultLeft, resultRight, calcul[i] );

                return result;
            }
        }

        //cherche et réalise les multiplications et les divisions en itérant depuis la fin
        for ( int i = std::size(calcul) - 1; i >= 0; --i )
        {
            if ( calcul[i] == '*' || calcul[i] == '/' )
            {
                calculLeft = { std::begin(calcul), std::begin(calcul) + i };
                resultLeft = doCalcul(calculLeft);

                calculRight = { std::begin(calcul) + i + 1, std::end(calcul) };
                resultRight = doCalcul(calculRight);

                //vérifie si le résultat correspond à une erreure
                if ( resultLeft == std::numeric_limits<double>::max() || resultRight == std::numeric_limits<double>::max() )
                {
                    return result = std::numeric_limits<double>::max();
                }

                result = doOperation( resultLeft, resultRight, calcul[i] );

                return result;
            }
            else
            {
                if ( isDouble(calcul) )
                {
                    result = stod(calcul);
                }
                else
                {
                    //affecte la valeur d'erreur à result
                    result = std::numeric_limits<double>::max();
                }
            }
        }

        return result;
    }
}
