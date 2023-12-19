#ifndef CALC_H
#define CALC_H


#define PI 3.14159265358979323846

#define degreesToRadians(degrees) ((degrees * PI) / 180.0)

#define radiansToDegrees(radians) ((radians * 180) / PI)

enum mathOperation {
  Sine,
  Cosine,
  Tangent,
  aSine,
  aCosine,
  aTangent,
  Logarithm,
  Factorial,
  SquareRoot,
  Exponential,
  Modulo,
  Division,
  Multiplication,
  Addition,
  Subtraction,
  Null
};

enum bracketAssociativity {
  LEFT,
  RIGHT
};

enum tokenType {
  NUMBER = -1,
  OPERATOR = 0,
  BRACKET = 3,
  FUNCTION = 1,
  COMMA = 5,
  LEFT_BRACKET = 2,
  RIGHT_BRACKET = 3,
};


#endif