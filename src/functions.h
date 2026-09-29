#include <string>

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

namespace function
{
    class Function
    {
    public:
        std::string getName() const { return m_name; }
        void setName( std::string name ) { m_name = name; }

        std::string getResult() const { return m_result; }
        void setResult( std::string result ) { m_result = result; }

        bool find( const std::string& calcul, std::string::iterator parenthesesBegin, std::string::iterator parenthesesEnd );

    private:
        std::string m_name{};
        std::string m_result{};
    };
}

#endif
