
#include "token.h"
#include "calc.h"
#include "math.h"

#include <string>


Token::Token(tokenType typeInput, int precedenceInput, bracketAssociativity associativityInput, std::string valueInput, mathOperation operationInput) {
    type = typeInput;
    precedence = precedenceInput;
    associativity = associativityInput;
    value = valueInput;
    operation = operationInput;
}


double Token::math(double x, double y, bool isRadians) {

    switch (operation) {

        case Sine:       if (isRadians) return sin(x); else return sin(degreesToRadians(x));
        case Cosine:     if (isRadians) return cos(x); else return cos(degreesToRadians(x));
        case Tangent:    if (isRadians) return tan(x); else return tan(degreesToRadians(x));
        case aSine:      if (isRadians) return asin(x); else return asin(radiansToDegrees(x));
        case aCosine:    if (isRadians) return acos(x); else return acos(radiansToDegrees(x));
        case aTangent:   if (isRadians) return atan(x); else return atan(radiansToDegrees(x));
        case Logarithm:  return log(x);
        case Factorial:  return tgamma(x + 1);
        case SquareRoot: return sqrt(x);

        case Exponential:    return pow(x, y);
        case Modulo:         return int(x) % int(y);
        case Division:       return x / y;
        case Multiplication: return x * y;
        case Addition:       return x + y;
        case Subtraction:    return x - y;

        // case Null: std::cout << "well crap, there is a bug." << std::endl;

        // default: std::cout << "this isn't suppsed to happen..." << std::endl;

    }
    return 0.0;
}

