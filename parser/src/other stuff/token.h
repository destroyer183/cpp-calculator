
#ifndef TOKEN_H
#define TOKEN_H


#include <string>

#include "calc.h"



class Token {

    public:

        tokenType type;
        bracketAssociativity associativity;
        mathOperation operation;
        int precedence;
        std::string value;

        Token(tokenType typeInput = tokenType::FUNCTION,
              int precedenceInput = 0,
              bracketAssociativity associativityInput = LEFT,
              std::string valueInput = "",
              mathOperation operationInput = Null);

        double math(double x, double y, bool isRadians);
};


#endif