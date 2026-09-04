#include "calculator.h"
#include "utils.h"

#include <string>
#include <cmath>
#include <optional>

namespace calc
{
    struct Calcul
    {
        char symbol {};
        std::optional<double> resultLeft {};
        std::optional<double> resultRight {};
        std::string calculLeft {};
        std::string calculRight {};
    };

    std::optional<double> doOperation( Calcul operationStruct )
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

    std::optional<double> doCalcul( const std::string& calcul )
    {
        if (calcul == "pi()")
        {
            return M_PI;
        }

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

    /*doParentheses( std::string calcul )
    {
        while ( calcul.find("("))
        {
            int debutParentheses {};
            int finParentheses {};

            for ( int i = 0; i < std::size(calcul); ++i )
            {
                if ( calcul[i] == '(' )
                {
                    debutParentheses = i;
                }
                if ( calcul[i] == ')' )
                {
                    finParentheses = i;
                }
            }
        }
    }*/
}
