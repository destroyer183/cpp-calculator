/*
  Student Name: Jacob Zante
  Course Code: TEJ3M
  Teacher: Mr. So
  Project Name: Scientific Calculator
  Project Description: This is a scientific calculator that can solve large equations with proper order of operations.
  Date of Completion: Dec 21, 2023
*/


/*
  NOTE:
  while the format for some of the if statements and switch statements 
  is incorrect, it is far simpler to read and understand 
  exactly what is happening for each condition when 
  every output is lined up above and below each other, 
  rather than being separated by multiple lines.

  places where it is used: 
  math() function in token class
  charToInt() function
  binaryConverter() function
  serialHandler() function
*/


/*
  NOTE:
  the syntax for macros is very specific, 
  meaning that comments can't be placed on multi-line macros,
  and so I have instead wrote the comments line by line above the macro declaration.
*/



#include <ArxContainer.h> // include library for vectors and deques
#include <math.h> // include library for math functions
#include <LiquidCrystal.h> // include library for LCD
#include <Keypad.h> // include library for 4x3 keypad




#define defineToken(type, precedence, associativity, value, operation) TOKENS.push_back(Token(type, precedence, associativity, value, operation)) // make macro to improve syntax for making a new token


#define PI 3.14159265358979323846 // make macro for pi


#define degreesToRadians(degrees) ((degrees * PI) / 180.0) // make macro to convert a number from degrees to radians
#define radiansToDegrees(radians) ((radians * 180) / PI) // make macro to convert a number from radians to degrees


// make macro to reuse code for removing element from one array and putting it on another
// line 1: assign temporary variable to the last element in the stack that will be losing an element
// line 2: add temporary variable to stack that is gaining an element
// line 3: remove last element in the stack that is losing an element
#define popAppend(temp, popStack, appendStack) ({\
    temp = popStack.back();\
    appendStack.push_back(temp);\
    popStack.pop_back();\
  })


int decimalPoints; // define variable to hold value of decimal places to round to

const int icPins[] = {23, 25, 27, 29}; // define array to hold pin numbers for pins connected to the 4511 IC

bool manualOverride = false; // variable to represent whether the serial input manual override is enabled

const int ROW_NUM = 4; // define variable to represent the number of rows in the keypad
const int COLUMN_NUM = 3; // define variable to represent the number of columns in the keypad

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'-', '0', '.'}
}; // define 2d array to hold information for the keypad

byte pinRows[ROW_NUM] = {31, 33, 35, 37}; // define array to hold pin numbers for row connections from the keypad
byte pinColumns[COLUMN_NUM] = {39, 41, 43}; // define array to hold pin numbers for column connections from the keypad

Keypad keypad = Keypad(makeKeymap(keys), pinRows, pinColumns, ROW_NUM, COLUMN_NUM); // initialize keypad

bool isRadians = false; // define boolean value to represent whether or not the calculator should perform calculations in Radians or Degrees

LiquidCrystal lcd{13, 12, 11, 10, 9, 8}; // initialize LCD

String equationString = ""; // define variable to hold the inputted equation
String numberString = ""; // define variable to hold inputted numbers



enum mathOperation {
  Sine,
  Cosine,
  Tangent,
  ArcSine,
  ArcCosine,
  ArcTangent,
  Logarithm,
  Factorial,
  SquareRoot,
  Exponential,
  Modulus,
  Division,
  Multiplication,
  Addition,
  Subtraction,
  Null
}; // enumeration for mathematical operations


enum Associativity {
  LEFT,
  RIGHT
}; // enumeration for directional associativity

enum tokenType {
  NUMBER = -1,
  OPERATOR = 0,
  FUNCTION = 1,
  LEFT_BRACKET = 2,
  RIGHT_BRACKET = 3,
}; // enumeration for different types of tokens


class Token { // define token class to handle certain characters and data that should be associated with them

  public: // define public scope

    tokenType type; // declare variable to hold the type of token associated with a string
    Associativity associativity; // declare variable to hold the directional associativity associated with a string
    mathOperation operation; // declare variable to hold the type of math operation associated with a string
    int precedence; // declare variable to hold the precedence of an operator in the order of operations
    String value; // declare variable to store token data

    Token(tokenType typeInput = FUNCTION, int precedenceInput = 0, Associativity associativityInput = LEFT, String valueInput = "", mathOperation operationInput = Null) { // define constructor function to assign attributes
      type = typeInput; // assign token type attribute to inputted type
      precedence = precedenceInput; // assign token precedence attribute to inputted precedence
      associativity = associativityInput; // assign token associativity to inputted associativity
      value = valueInput; // assign token value to inputted value
      operation = operationInput; // assign token operation type to inputted operation
    }

    
    double math(double x, double y, bool isRadians) { // function to perform simple mathematical calculations depending on the type of operator/function being used.

      switch (operation) { // use a switch statement on the 'operation' variable
        case Sine:       if (isRadians) return sin(x);  else return sin(degreesToRadians(x)); // calculate the Sine of 'x' in either radians or degrees
        case Cosine:     if (isRadians) return cos(x);  else return cos(degreesToRadians(x)); // calculate the Cosine of 'x' in either radians or degrees
        case Tangent:    if (isRadians) return tan(x);  else return tan(degreesToRadians(x)); // calculate the Tangent of 'x' in either radians or degrees
        case ArcSine:    if (isRadians) return asin(x); else return asin(radiansToDegrees(x)); // calculate the ArcSine of 'x' in either radians or degrees
        case ArcCosine:  if (isRadians) return acos(x); else return acos(radiansToDegrees(x)); // calculate the ArcCosine of 'x' in either radians or degrees
        case ArcTangent: if (isRadians) return atan(x); else return atan(radiansToDegrees(x)); // calculate the ArcTangent of 'x' in either radians or degrees
        case Logarithm:  return log(x); // calculate the Logarithm of 'x'
        case Factorial:  {int factorial = 1; if (x < 0) return 0; else for (int i = 1; i <= x; ++i) {factorial *= i;} return factorial;} // calculate the Factorial of 'x'
        case SquareRoot: return sqrt(x); // calculate the square root of 'x'

        case Exponential:    return pow(x, y); // calculate 'x' to the power of 'y'
        case Modulus:        return int(x) % int(y); // calculate 'x' modulus 'y'
        case Division:       return x / y; // calculate 'x' divided by 'y'
        case Multiplication: return x * y; // calculate 'x' multiplied by 'y'
        case Addition:       return x + y; // calculate 'x' plus 'y'
        case Subtraction:    return x - y; // calculate 'x' minus 'y'
      }
      Serial.println("bug in class"); // print text if the function bugs
      return 0.0; // add return statement to avoid problems if no switch case triggers
    }
};


arx::deque<Token> TOKENS; // declare array to hold tokens


void makeTokens() { // fill array with tokens that represent mathematical operators and functions

  defineToken(FUNCTION, 5, LEFT, "s", Sine); // create token for Sine function and add it to an array with a macro
  defineToken(FUNCTION, 5, LEFT, "c", Cosine); // create token for Cosine function and add it to an array with a macro
  defineToken(FUNCTION, 5, LEFT, "t", Tangent); // create token for Tangent function and add it to an array with a macro
  defineToken(FUNCTION, 5, LEFT, "S", ArcSine); // create token for ArcSine function and add it to an array with a macro
  defineToken(FUNCTION, 5, LEFT, "C", ArcCosine); // create token for ArcCosine function and add it to an array with a macro
  defineToken(FUNCTION, 5, LEFT, "T", ArcTangent); // create token for ArcTangent function and add it to an array with a macro
  defineToken(FUNCTION, 5, LEFT, "l", Logarithm); // create token for Logarithm function and add it to an array with a macro
  defineToken(FUNCTION, 4, LEFT, "f", Factorial); // create token for Factorial function and add it to an array with a macro
  defineToken(FUNCTION, 2, LEFT, "#", SquareRoot); // create token for Square Root function and add it to an array with a macro

  defineToken(OPERATOR, 3, RIGHT, "^", Exponential); // create token for Exponential operator and add it to an array with a macro
  defineToken(OPERATOR, 1, LEFT,  "%", Modulus); // create token for Modulus operator and add it to an array with a macro
  defineToken(OPERATOR, 1, LEFT,  "/", Division); // create token for Division operator and add it to an array with a macro
  defineToken(OPERATOR, 1, LEFT,  "*", Multiplication); // create token for Multiplication operator and add it to an array with a macro
  defineToken(OPERATOR, 0, LEFT,  "+", Addition); // create token for Addition operator and add it to an array with a macro
  defineToken(OPERATOR, 0, LEFT,  "_", Subtraction); // create token for Subtraction operator and add it to an array with a macro

  defineToken(LEFT_BRACKET,  0, RIGHT, "(", Null); // create token for left bracket and add it to an array with a macro
  defineToken(RIGHT_BRACKET, 0, LEFT,  ")", Null); // create token for right bracket and add it to an array with a macro
}



double charToInt(char input) { // function to convert a single character into an integer

  switch (input) { // switch statement with 'input' variable
    case '1': return 1; // return the integer version of every char that is a number
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    case '0': return 0;
  }
}

// function to convert a string to a double
double stringToDouble(String input) {

  double output = 0; // create variable to store output number

  bool negative = false; // create variable to denote whether or not the number is negative
  bool decimal = false; // create variable to denote whether or not the current iteration loop is a decimal number or not
  int decimalIndex = 0; // create variable to store the number of decimal places found

  for (char i : input) { // loop over every char in the input string

    double num = charToInt(i); // convert the char to an integer

    if (decimal) { // check if the current iteration loop is at a decimal point
      decimalIndex++; // increase decimal index
    }

    if (i == '-') { // check if the current character is a negative sign
      negative = true; // change number to be negative
      continue; // skip the rest of the following code in this loop to begin a new loop
    }
    if (i == '.') { // check if the current character is a decimal point
      decimal = true; // change variable to show that a decimal point has been found
      continue; // skip the rest of the following code in this loop to begin a new loop
    }


    else if (num == 0) { // check if inputted number is a zero
      if (!decimal) output *= 10; // multiply output number by 10 to add a zero to the end of it
    }

    else { // do something if none of the above if statements triggered

      if (decimal) { // check if the current iteration loop is a decimal number or not
        output += num / (pow(10, decimalIndex)); // divide the current integer by the number of decimal places found and add it to the output number
      }

      else { // do something if the above if statement didn't trigger
        output = output * 10 + num; // multiply the output number by 10 and then add the integer to it
      }
    }

  }

  if (negative) { // check if the number is a negative number
    output *= -1; // multiply the number by -1 to make it negative
  }

  return output; // return output number
}



// double roundNumber(double number, int decimals) { // function to round a double to a variable number of decimal places

//   double multiplier = pow(10, decimals); // create variable to represent how many decimal places need to be maintained

//   number *= multiplier; // multiply input number by the multiplier to move all necessary decimal numbers to the left of the decimal point

//   number = round(number); // round number to the nearest integer

//   number /= multiplier; // divide number by the multiplier to return all maintained decimal numbers to the right of the decimal point

//   return number; // return output number
// }



int findElement(String stack, String element) { // function to check if an element is contained within a larger string

  Serial.print("element: "); // print text to show the element to be searched for
  Serial.println(element); // print the element

  for (char i : stack) { // loop over every character in string
    if (element == String(i)) { // check if element matches character
      return 1; // return a 1 if there is a match
    }
  }
  return -1; // return a -1 if no match is found
}




Token getToken(String input) { // function to either return a token that already exists, or make a new one for a number.

  Serial.print("input: "); // print text to show the inputted string
  Serial.println(input); // print the inputted string

  
  for (int i = 0; i < TOKENS.size(); i++) { // loop through all math tokens

    
    if (TOKENS[i].value == input) { // check if inputted value is equal to any existing tokens

      Serial.print("token set: "); // print text to show the new token
      Serial.println(TOKENS[i].value); // print the value of the element at an index of the token array

      return TOKENS[i]; // return matching existing token

    }
  }

  
  Token temp; // declare new token

  // set attributes of new token
  temp.type = NUMBER; // assign token type to be a number
  temp.precedence = 0; // assign token precedence to 0
  temp.associativity = LEFT; // assign token associativity to left
  temp.value = input; // assign token value to the inputted string

  Serial.print("number set: "); // print text to show the new number
  Serial.println(temp.value); // print the token value

  return temp;// return new token

}


// make macro to reuse code for removing value from input and turning it into a token
// line 1: set temporary variable to be the first element in the input stack
// line 2: remove the first element in the input stack
// line 3: convert the temporary variable to a token and assign it to the token variable
#define newToken(input, stack, token) ({\
    input = stack.front();\
    stack.pop_front();\
    token = getToken(input);\
  })




arx::deque<Token> shuntingYardConverter(String equation) { // main function for converting regular math equation into reverse polish notation

  arx::deque<String> inStack; // declare input stack
  arx::deque<Token> opStack; // declare operator stack
  arx::deque<Token> outStack; // declare output stack
  arx::deque<String> tempStack; // declare temporary stack
  String characters = "1234567890.-"; // define characters for searching for a number

  Token token; // declare main token
  Token temp; // declare temporary token

  String nums; // declare variable to hold data for concatenating an array of strings into a single string
  String input; // declare variable to simplify code for making a new token

  

  
  for (char c : equation) { // loop over every character in the input equation
    inStack.push_back(String(c)); // convert character to a string and add it to the input stack
  }

  Serial.print("size: "); // print data to show the number of elements in the inputted equation
  Serial.println(inStack.size()); // print size of input stack

  Serial.print("original deque: "); // print out the original stack before conversion

  for (int i = 0; i < inStack.size(); i++) { // loop over every element in the input stack by index
    Serial.print(inStack[i]); // print element
  }

  Serial.println(); // print new line

  while (inStack.size() > 0 && inStack.size() < 1000) { // while loop to keep looping over input stack until every element has been removed from it

    tempStack = {}; // define temporary array as empty array

    newToken(input, inStack, token); // create new token from first element of input array

    
    if (token.value == " ") { // check if token is a whitespace
      Serial.println("whitespace skipped"); // print out confirmation of the above if statement
      continue; // skip loop if token is a whitespace
    }

    
    if (token.type == NUMBER) { // check if the new token is a number

      if (findElement(characters, token.value) != -1) { // check if token value is a character that belongs in a number

        while (findElement(characters, token.value) != -1) { // keep looping until first element of input stack is not a character that belongs in a number

          Serial.println("number found\n"); // print text to show that a number has been found

          tempStack.push_back(token.value); // add number token to temporary stack

          if (inStack.size() > 0) { // check if input stack is not empty

            newToken(input, inStack, token); // remove first element of input stack and make it a token

          } else break; // exit loop if input stack is empty
        }

        nums = ""; // define placeholder string as emptry string

        for (int i = 0; i < tempStack.size(); i++) { // loop over every element of the temporary stack by index
          nums += tempStack[i]; // add element at index to placeholder string
        }

        Serial.print("new number: "); // print out data to show full new number
        Serial.println(nums);
        Serial.println("token.type: -1\n");

        temp = getToken(nums); // make placeholder string a token and assign it to placeholder token

        outStack.push_back(temp); // add new token to output stack
      }

    }

    if (token.type == FUNCTION) { // check if token is a function

      opStack.push_back(token); // add token to output stack
    }


    else if (token.type == OPERATOR) { // check if token is operator

      // keep looping while:
      // operator stack size is not 0 and the last token in the operator stack is not a left bracket, and the statement
      // the precedence of the last element in the operator stack is greater than the precedence of the current token, or the statement
      // the precedence of the last element in the operator stack is equal to the precedence of the current token, and
      // the current token is right-associated
      while (opStack.size() > 0 && opStack.back().value != "(" && (
              opStack.back().precedence > token.precedence || (
              opStack.back().precedence == token.precedence &&
              token.associativity))) {

        popAppend(temp, opStack, outStack); // remove last element from operator stack and put it on output stack

      }

      opStack.push_back(token); // place current token on the back of the operator stack
    }



    else if (token.type == LEFT_BRACKET) { // check if current token is a left bracket

      opStack.push_back(token); // place current token on the back of the operator stack
    }



    else if (token.type == RIGHT_BRACKET) { // check if current token is a right bracket

      
      while (opStack.size() > 0 && opStack.back().type != LEFT_BRACKET) { // keep looping while the operator stack is not empty and the last token in the operator stack is not a left bracket

        popAppend(temp, opStack, outStack); // remove last element from operator stack and put it on output stack

      }

      opStack.pop_back(); // remove last element from operator stack (will always be a left bracket in this situation)
    }
  }



  while (opStack.size() > 0) { // keep looping while the operator stack is not emptry
    popAppend(temp, opStack, outStack); // remove last element from operator stack and put it on the output stack
  }


  Serial.print("equation in RPN: "); // print the new equation in reverse polish notation

  for (int i = 0; i < outStack.size(); i++) { // loop over every element in the output stack by index
    Serial.print(outStack[i].value); // print output stack element at index
    Serial.print(" "); // print space
  }

  Serial.println(); // print new line

  return outStack; // return output stack
}



arx::vector<double> findNumbers(tokenType type, arx::deque<double> hist) { // function to find the numbers needed for a math operation/function


  if (type == FUNCTION) { // check if token type is a function
    return arx::vector<double> {hist[hist.size() - 1], 0.0}; // only return one number from the end of the number history if it is for a function, and return a 0
  }

  
  else if (type == OPERATOR) { // check if token type is an operator
    return arx::vector<double> {hist[hist.size() - 2], hist.back()}; // return two numbers from the end of the number history if it is for an operation
  }

  return arx::vector<double> {0.0, 0.0}; // return two zeroes if neither if statement triggers
}



double shuntingYardEvaluator(arx::deque<Token> equation, bool isRadians = false) { // main function for evaluating and solving equation once it is in reverse polish notation

  arx::deque<Token> stack = equation; // define variable to hold inputted equation

  arx::deque<double> hist = {}; // define empty array to hold numbers

  Token token; // declare token to hold first element of input stack

  while (stack.size() > 0 && stack.size() < 10000) { // keep looping while input stack is not empty, and while the input stack hasn't overflowed

    token = stack.front(); // set token to first token in input stack

    stack.pop_front(); // remove first token in input stack

    if (token.type == NUMBER) { // check if token is a number

      hist.push_back(stringToDouble(token.value)); // put just the number on the back of the number stack, after converting it from a string to a double
    }

    else { // do something different if the if statement above doesn't trigger

      arx::vector<double> arr = findNumbers(token.type, hist); // define variable that holds the necessary numbers for the current math function/operation

      double x = arr[0]; // make a variable to store the first number for a portion of the equation
      double y = arr[1]; // make a variable to store the second number for a portion of the equaiton


      Serial.print("num1: "); // print data for the first number
      Serial.println(x); // print the value of x
      Serial.print("num2: "); // print data for the second number
      Serial.println(y); // print the value of y
      Serial.print("operation: "); // print data for the type of operation
      Serial.println(token.value); // print the token value

      hist.pop_back(); // remove last element from number history, since it is being changed by the current operation/function

      if (!token.type) hist.pop_back(); // remove 2nd last item from number history if an operation is being used

      double output = Serial.println(token.math(x, y, isRadians)); // evaluate math operation/function and assign it to a variable
      hist.push_back(output); // add output to the number history

    }
  }

  
  return hist[0]; // return the only element left in the number history, which is the solution of the inputted equation.

}



void solve(String equation = equationString) { // function to solve inputted equation

  arx::deque<Token> stack = shuntingYardConverter(equation); // convert inputted equation to reverse polish notation and assign it to a variable

  Serial.print("equation in RPN: "); // print text to show equation in reverse polish notation

  for (int i = 0; i < stack.size(); i++) { // loop over every element in the output stack by index
    Serial.print("value: "); // print text to show the value of each token
    Serial.println(stack[i].value); // print the token value of the token at an index of the stack
    Serial.print("type: "); // print text to show the type of a token
    Serial.println(stack[i].type); // print the token type of the token at an index of the stack
    Serial.println(); // print new line
  }

  Serial.println(); // print another new line


  double solution = shuntingYardEvaluator(stack, isRadians); // solve converted equation and assign the output to a variable

  Serial.print("solution: "); // print text to show the solution of the equation
  Serial.println(solution, decimalPoints); // print solution with additional argument to denote how many decimal points to round to

  equationString += " ="; // add equals sign to the equation
  numberString = solution; // set the number string to the solution

}



arx::deque<int> binaryConverter(int input) { // function to convert a decimal number to a binary number

  switch (input) { // switch statement with input variable
    case 1: return {0, 0, 0, 1}; // return binary number for each integer case from 0 to 9
    case 2: return {0, 0, 1, 0};
    case 3: return {0, 0, 1, 1};
    case 4: return {0, 1, 0, 0};
    case 5: return {0, 1, 0, 1};
    case 6: return {0, 1, 1, 0};
    case 7: return {0, 1, 1, 1};
    case 8: return {1, 0, 0, 0};
    case 9: return {1, 0, 0, 1};
    case 0: return {0, 0, 0, 0};
  }
  return {0}; // return array if no switch case triggers
}


void updateDisplay() { // function to update the LCD

  lcd.setCursor(0, 0); // set cursor location to (0, 0) on the LCD

  for (char i : equationString) { // loop over every character in the equation string
    lcd.print(i); // print character to the serial monitorff
  }

  lcd.setCursor(0, 1); // set cursor location to (0, 1) on the LCD

  lcd.print("                "); // print whitespace to erase previous number

  lcd.setCursor(0, 1); // set cursor location back to (0, 1) on the LCD

  lcd.print(numberString); // print the number string to the LCD
}


void decimalRound() { // function to take a resistance value from a potentiometer and convert it to an integer from 0 to 9 and display it on a 7-segment display

  decimalPoints = analogRead(A0); // read resistance value on analog pin 0

  decimalPoints = map(decimalPoints, 0, 1023, 0, 10); // reduce value to a range of 0 to 9

  arx::deque<int> binaryValues = binaryConverter(decimalPoints); // convert integer number into binary number

  digitalWrite(icPins[3], binaryValues[3]); // send output to 4th IC pin
  digitalWrite(icPins[0], binaryValues[2]); // send output to 3rd IC pin
  digitalWrite(icPins[1], binaryValues[1]); // send output to 2nd IC pin
  digitalWrite(icPins[2], binaryValues[0]); // send output to 1st IC pin

}


void clearData() { // function to clear the data stored in the equation string and the number string

  equationString = ""; // set equation string to an empty string
  numberString = ""; // set number string to an empty string

  lcd.setCursor(0, 0); // set cursor to (0, 0) on the LCD
  lcd.print("                "); // print whitespace to clear previous equation
}

void serialHandler(String input) { // function to handle serial inputs

  equationString += numberString; // add number data to the equation
  numberString = ""; // clear number data

  if (input == "Sine"       || input == "sin")  equationString += "s("; // add Sine function to equation
  if (input == "Cosine"     || input == "cos")  equationString += "c("; // add Cosine function to equation
  if (input == "Tangent"    || input == "tan")  equationString += "t("; // add Tangent function to equation
  if (input == "ArcSine"    || input == "asin") equationString += "S("; // add ArcSine function to equation
  if (input == "ArcCosine"  || input == "acos") equationString += "C("; // add ArcCosine function to equation
  if (input == "ArcTangent" || input == "atan") equationString += "T("; // add ArcTangent function to equation
  if (input == "Logarithm"  || input == "log")  equationString += "l("; // add Logarithm function to equation
  if (input == "Factorial"  || input == "!")    equationString += "f("; // add Factorial function to equation
  if (input == "SquareRoot" || input == "sqrt") equationString += "#("; // add Square Root function to equation

  if (input == "Exponential"    || input == "^") equationString += " ^ "; // add Exponential operator to equation
  if (input == "Modulus"        || input == "%") equationString += " % "; // add Modulus operator to equation
  if (input == "Division"       || input == "/") equationString += " / "; // add Division operator to equation
  if (input == "Multiplication" || input == "*") equationString += " * "; // add Multiplication operator to equation
  if (input == "Addition"       || input == "+") equationString += " + "; // add Addition operator to equation
  if (input == "Subtraction"    || input == "-") equationString += " _ "; // add Subtraction operator to equation

  if (input == "(") equationString += "("; // add left bracket to equation
  if (input == ")") equationString += ")"; // add right bracket to equation

  if (input == "clear") clearData(); // run function to clear data
  if (input == "solve") solve(); // run function to solve equation

  if (input == "Radians") isRadians = true;  Serial.println("mode set to Radians."); // change calculator mode to Radians
  if (input == "Degrees") isRadians = false; Serial.println("mode set to Degrees."); // change calculator mode to Degrees

  if (input == "ENABLE MANUAL OVERRIDE")  manualOverride = true;  Serial.println("manual override enabled."); // enable manual override. This allows the user to
                                                                                                              // type in entire equations into the serial monitor, 
                                                                                                              // rather than single functions and operators at a time.

  if (input == "DISABLE MANUAL OVERRIDE") manualOverride = false; Serial.println("manual override disabled."); //disable manual override
}





void setup() { // setup code to be rn once

  Serial.begin(9600); // initialize the serial monitor with 9600 baud

  lcd.begin(16, 2); // initialize the LCD

  makeTokens(); // creaee all tokens and put them in an array

  pinMode(A0, INPUT); // set analog pin 0 as an input

  for (int i : icPins) { // loop over every element in the icPins array
    pinMode(i, OUTPUT); // set pin as an output
  }

}

void loop() { // loop code to run indefinitely

  decimalRound(); // run function to handle the round number input from the potentiometer

  //  String equation = "4 + (f(3) * (52 + 73 * #(64) / 2 _ 220) _  2 ^ (5 _ 2)) / 15"; // equation for testing

  updateDisplay(); // run function to keep the display updated

  delay(50); // delay of 50ms to keep the code runninng in a stable fashion

  char key = keypad.getKey(); // take input from keypad

  if (key) { // check if a key has been pressed
    numberString += String(key); // add the value of the key to the number string
    Serial.print("\nnumber: "); // print text to show the new number
    Serial.println(numberString); // print the number string
    Serial.print("equation: "); // print text to show the current equation
    Serial.println(equationString); // print the equation string
  }

  if (Serial.available()) { // check if a serial input has been made
    if (manualOverride) { // check if manual override is enabled
      String input = Serial.readString(); // read the serial input and assign it to a variable
      serialHandler(input); // send the variable to the serial handler
      equationString = input; // assign the equation string to the serial input
      solve(); // solve the current equation
    } 
    
    else { // do something different if manual override isn't enabled
      String input = Serial.readString(); // read the serial input and assign it to a variable
      serialHandler(input); // send the variable to the serial handler
      Serial.print("\nequation: "); // print text to show the current equation
      Serial.println(equationString); // print the equation string
    }
  }
}