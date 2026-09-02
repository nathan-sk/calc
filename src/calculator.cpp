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

    double doOperation( Calcul operationStruct )
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
                return *operationStruct.resultLeft / *operationStruct.resultRight;
            case '^':
                return pow( *operationStruct.resultLeft, *operationStruct.resultRight );
        }

        return 0;
    }

    std::optional<double> doCalcul( const std::string& calcul )
    {
        if (calcul == "pi()")
        {
            return 3.1415;
        }

        for(int x{0}; x < 3; ++x)
        {
            //cherche et réalise les additions et les soustractions en itérant depuis la fin
            for ( int i = std::size(calcul) - 1; i >= 0; --i )
            {
                char symbol1{};
                char symbol2{};

                if (x == 0) { symbol1 = '+'; symbol2 = '-'; }
                if (x == 1) { symbol1 = '*'; symbol2 = '/'; }
                if (x == 2) { symbol1 = '^'; symbol2 = '^'; }

                if ( (calcul[i] == symbol1  || calcul[i] == symbol2) && (i != 0) && (isdigit(calcul[i-1])) )
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
}
