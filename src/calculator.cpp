#include "calculator.h"
#include "utils.h"

#include <string>
#include <limits>

namespace calc
{
    struct Calcul
    {
        char symbol {};
        double resultLeft {};
        double resultRight {};
        std::string calculLeft {};
        std::string calculRight {};
    };

    double doOperation( Calcul operationStruct )
    {
        switch (operationStruct.symbol)
        {
            case '+':
                return operationStruct.resultLeft + operationStruct.resultRight;
            case '-':
                return operationStruct.resultLeft - operationStruct.resultRight;
            case '*':
                return operationStruct.resultLeft * operationStruct.resultRight;
            case '/':
                return operationStruct.resultLeft / operationStruct.resultRight;
        }

        return 0;
    }

    double doCalcul( const std::string& calcul )
    {
        //cherche et réalise les additions et les soustractions en itérant depuis la fin
        for ( int i = std::size(calcul) - 1; i >= 0; --i )
        {
            if ( calcul[i] == '+' || calcul[i] == '-' )
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
                if (isError(calculStruct.resultLeft, calculStruct.resultRight)) { return std::numeric_limits<double>::max(); }

                return  doOperation( calculStruct );
            }
        }

        //cherche et réalise les multiplications et les divisions en itérant depuis la fin
        for ( int i = std::size(calcul) - 1; i >= 0; --i )
        {
            if ( calcul[i] == '*' || calcul[i] == '/' )
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
                if (isError(calculStruct.resultLeft, calculStruct.resultRight)) { return std::numeric_limits<double>::max(); }

                return  doOperation( calculStruct );
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
            return std::numeric_limits<double>::max();
        }
    }
}
