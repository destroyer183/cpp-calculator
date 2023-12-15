
#ifndef TOKEN_H
#define TOKEN_H



#include "calc.h"



class Token {

    public:

        tokenType type;
        bracketAssociativity associativity;
        mathOperation operation;
        int precedence;
        String value;

        Token(tokenType typeInput = tokenType::FUNCTION,
              int precedenceInput = 0,
              bracketAssociativity associativityInput = LEFT,
              String valueInput = "",
              mathOperation operationInput = Null);

        double math(double x, double y, bool isRadians);
};


#endif