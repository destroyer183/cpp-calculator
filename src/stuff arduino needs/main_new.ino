/* 
Student Name: Jacob Zante
Course Code: TEJ3M
Teacher: Mr. So
Project Name: Scientific Calculator
Project Description: This is a scientific calculator that can solve large equations with proper order of operations.
Date of Completion: Dec 21, 2023
*/



#include <ArxContainer.h> // include library for vectors and deques
#include <math.h> // include library for math functions
#include <LiquidCrystal.h> // include library for LCD
#include <Keypad.h> // include library for 4x3 keypad



// make macro to improve syntax for making a new token
#define defineToken(type, precedence, associativity, value, operation) TOKENS.push_back(Token(type, precedence, associativity, value, operation))

// make macro for pi
#define PI 3.14159265358979323846

// make macro to convert from degrees to radians and vice versa
#define degreesToRadians(degrees) ((degrees * PI) / 180.0)
#define radiansToDegrees(radians) ((radians * 180) / PI)

// make macro to reuse code for removing element from one array and putting it on another
#define popAppend(temp, popStack, appendStack) ({\
    temp = popStack.back();\
    appendStack.push_back(temp);\
    popStack.pop_back();\
  })



int analogOne; // define variable to hold value of analog pin

const int icPins[] = {23, 25, 27, 29}; // define array to hold pin numbers for pins connected to the 4511 IC

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

    // define constructor function to assign attributes
    Token(tokenType typeInput = FUNCTION, int precedenceInput = 0, Associativity associativityInput = LEFT, String valueInput = "", mathOperation operationInput = Null) {
      type = typeInput;
      precedence = precedenceInput;
      associativity = associativityInput;
      value = valueInput;
      operation = operationInput;
    }

    double math(double x, double y, bool isRadians) {

      switch (operation) {

        case Sine:       if (isRadians) return sin(x); else return sin(degreesToRadians(x));
        case Cosine:     if (isRadians) return cos(x); else return cos(degreesToRadians(x));
        case Tangent:    if (isRadians) return tan(x); else return tan(degreesToRadians(x));
        case ArcSine:    if (isRadians) return asin(x); else return asin(radiansToDegrees(x));
        case ArcCosine:  if (isRadians) return acos(x); else return acos(radiansToDegrees(x));
        case ArcTangent: if (isRadians) return atan(x); else return atan(radiansToDegrees(x));
        case Logarithm:  return log(x);
        case Factorial:  {
            int factorial = 1;
            if (x < 0) return 0;
            else for (int i = 1; i <= x; ++i) {
                factorial *= i;
              } return factorial;
          }
        case SquareRoot:     return sqrt(x);
        case Exponential:    return pow(x, y);
        case Modulus:        return int(x) % int(y);
        case Division:       return x / y;
        case Multiplication: return x * y;
        case Addition:       return x + y;
        case Subtraction:    return x - y;
      }
      Serial.println("bug in class");
      return 0.0;
    }
};


// declare array to hold tokens
arx::deque<Token> TOKENS;


// fill array with tokens that represent mathematical operators and functions
void makeTokens() {

  defineToken(FUNCTION, 5, LEFT, "s", Sine);
  defineToken(FUNCTION, 5, LEFT, "c", Cosine);
  defineToken(FUNCTION, 5, LEFT, "t", Tangent);
  defineToken(FUNCTION, 5, LEFT, "S", ArcSine);
  defineToken(FUNCTION, 5, LEFT, "C", ArcCosine);
  defineToken(FUNCTION, 5, LEFT, "T", ArcTangent);
  defineToken(FUNCTION, 5, LEFT, "l", Logarithm);
  defineToken(FUNCTION, 4, LEFT, "f", Factorial);
  defineToken(FUNCTION, 2, LEFT, "#", SquareRoot);

  defineToken(OPERATOR, 3, RIGHT, "^", Exponential);
  defineToken(OPERATOR, 1, LEFT,  "%", Modulus);
  defineToken(OPERATOR, 1, LEFT,  "/", Division);
  defineToken(OPERATOR, 1, LEFT,  "*", Multiplication);
  defineToken(OPERATOR, 0, LEFT,  "+", Addition);
  defineToken(OPERATOR, 0, LEFT,  "_", Subtraction);

  defineToken(LEFT_BRACKET,  0, RIGHT, "(", Null);
  defineToken(RIGHT_BRACKET, 0, LEFT,  ")", Null);
}


double charToInt(char input) { 

  switch (input) {
    case '1': return 1;
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

double stringToDouble(String input) {

  double output = 0;

  bool negative = false;
  bool decimal = false;
  int decimalIndex = 0;

  for (char i : input) {

    double num = charToInt(i);

    if (decimal) decimalIndex++;

    if (i == '-') {
      negative = true;
      continue;
    }
    if (i == '.') {
      decimal = true;
      continue;
    }


    else if (num == 0) {
      if (!decimal) output *= 10;
    }

    else {

      if (decimal) {
        output += num / (pow(10, decimalIndex));
      }

      else {
        output = output * 10 + num;
      }
    }

  }

  if (negative) {
    output *= -1;
  }

  return output;
}






int findElement(arx::deque<String> stack, String element) {

  for (int i = 0; i < stack.size(); i++) {
    if (element == stack[i]) {
      return i;
    }
  }
  return -1;
}



// function to either return a token that already exists, or make a new one for a number.
Token getToken(String input) {

  Serial.print("input: ");
  Serial.println(input);

  // loop through all math tokens
  for (int i = 0; i < TOKENS.size(); i++) {

    // check if inputted value is equal to any existing tokens
    if (TOKENS[i].value == input) {

      Serial.print("token set: ");
      Serial.println(TOKENS[i].value);

      // return matching existing token
      return TOKENS[i];

    }
  }

  // declare new token
  Token temp;

  // set attributes of new token
  temp.type = NUMBER;
  temp.precedence = 0;
  temp.associativity = LEFT;
  temp.value = input;

  Serial.print("number set: ");
  Serial.println(temp.value);

  // return new token
  return temp;

}


// make macro to reuse code for removing value from input and turning it into a token
#define newToken(input, stack, token) ({\
    input = stack.front();\
    stack.pop_front();\
    token = getToken(input);\
  })



// main function for converting regular math equation into reverse polish notation
arx::deque<Token> shuntingYardConverter(String equation) {

  arx::deque<String> inStack; // declare input stack
  arx::deque<Token> opStack; // declare operator stack
  arx::deque<Token> outStack; // declare output stack
  arx::deque<String> tempStack; // declare temporary stack
  arx::deque<String> characters{"1", "2", "3", "4", "5", "6", "7", "8", "9", "0", ".", "-"}; // define characters for searching for a number

  // declare main token and temporary token
  Token token;
  Token temp;

  // declare variables to hold temporary data for creating numbers
  String nums;
  String input;

  Serial.print("size: ");
  Serial.println(inStack.size());

  // add every element from input to the input array
  for (char c : equation) {
    inStack.push_back(String(c));
  }

  Serial.print("original deque: ");

  for (int i = 0; i < inStack.size(); i++) {
    Serial.print(inStack[i]);
  }

  Serial.println();

  // while loop to keep looping over input stack until every element has been removed from it
  while (inStack.size() > 0 && inStack.size() < 1000) {

    // define temporary array as empty array
    tempStack = {};

    // create new token from first element of input array
    newToken(input, inStack, token);

    // skip loop if token is a whitespace
    if (token.value == " ") {
      continue;
    }

    // check if the new token is a number
    if (token.type == NUMBER) {

      // check if token value is a character that belongs in a number
      if (findElement(characters, token.value) != -1) {

        // keep looping until first element of input stack is not a character that belongs in a number
        while (findElement(characters, token.value) != -1) {

          Serial.println("number found\n");

          // add number token to temporary stack
          tempStack.push_back(token.value);

          // check if input stack is not empty
          if (inStack.size() > 0) {

            // remove first element of input stack and make it a token
            newToken(input, inStack, token);

            // exit loop if input stack is empty
          } else break;
        }

        // define placeholder string as emptry string
        nums = "";

        // loop through every digit in temporary stack and add it to placeholder string
        for (int i = 0; i < tempStack.size(); i++) {
          nums += tempStack[i];
        }

        Serial.print("new number: ");
        Serial.println(nums);
        Serial.println("token.type: -1\n");

        // make placeholder string a token and assign it to placeholder token
        temp = getToken(nums);

        // add new token to output stack
        outStack.push_back(temp);
      }

    }

    // check if token is a function
    if (token.type == FUNCTION) {

      // add token to output stack
      opStack.push_back(token);
    }


    // check if token is operator
    else if (token.type == OPERATOR) {

      // keep looping while:
      // operator stack size is not 0, and
      // the last token in the operator stack is not a left bracket, and the statement
      // the precedence of the last element in the operator stack is greater than the precedence of the current token, or the statement
      // the precedence of the last element in the operator stack is equal to the precedence of the current token, and
      // the current token is right-associated
      while (opStack.size() > 0 && opStack.back().value != "(" && (
               opStack.back().precedence > token.precedence || (
                 opStack.back().precedence == token.precedence &&
                 token.associativity))) {

        // remove last element from operator stack and put it on output stack
        popAppend(temp, opStack, outStack);

      }

      // place current token on the back of the operator stack
      opStack.push_back(token);

    }



    // check if current token is a left bracket
    else if (token.type == LEFT_BRACKET) {

      // place current token on the back of the operator stack
      opStack.push_back(token);
    }



    // check if current token is a right bracket
    else if (token.type == RIGHT_BRACKET) {

      // keep looping while the operator stack is not empty, and
      // the last token in the operator stack is not a left bracket
      while (opStack.size() > 0 && opStack.back().type != LEFT_BRACKET) {

        // remove last element from operator stack and put it on output stack
        popAppend(temp, opStack, outStack);

      }

      // remove last element from operator stack (will be a left bracket)
      opStack.pop_back();
    }
  }



  // remove every element from operator stack and put them on the output stack
  while (opStack.size() > 0) {
    popAppend(temp, opStack, outStack);
  }


  Serial.print("equation in RPN: ");

  for (int i = 0; i < outStack.size(); i++) {
    Serial.print(outStack[i].value);
    Serial.print(" ");
  }

  // std::cout << std::endl;
  Serial.println();

  // return output stack
  return outStack;
}


// function to find the numbers needed for a math operation/function
arx::vector<double> findNumbers(tokenType type, arx::deque<double> hist) {

  // only return one number from the end of the number history if it is for a function, and return a 0
  if (type == FUNCTION) {
    return arx::vector<double> {hist[hist.size() - 1], 0.0};
  }

  // return two numbers from the end of the number history if it is for an operation
  else if (type == OPERATOR) {
    return arx::vector<double> {hist[hist.size() - 2], hist.back()};
  }

  // return two zeroes if neither if statement triggers, this should never happen
  return arx::vector<double> {0.0, 0.0};
}



// main function for evaluating and solving equation once it is in reverse polish notation

double shuntingYardEvaluator(arx::deque<Token> equation, bool isRadians = false) {

  // define variable to hold inputted equation
  arx::deque<Token> stack = equation;

  // define empty array to hold numbers
  arx::deque<double> hist = {};

  // declare token to hold first element of input stack
  Token token;

  // keep looping while input stack is not empty
  while (stack.size() > 0 && stack.size() < 10000) {

    // set token to first token in input stack
    token = stack.front();

    // remove first token in input stack
    stack.pop_front();

    // check if token is a number
    if (token.type == NUMBER) {

      // put just the number on the back of the number stack, after converting it from a string to a double
      hist.push_back(stringToDouble(token.value));
    }

    else {

      // define variable that holds the necessary numbers for the current math function/operation
      arx::vector<double> arr = findNumbers(token.type, hist);

      // make two variable hold the two necessary numbers
      double x = arr[0];
      double y = arr[1];

      
      Serial.print("num1: ");
      Serial.println(x);
      Serial.print("num2: ");
      Serial.println(y);
      Serial.print("operation: ");
      Serial.println(token.value);

      // remove last element from number history, since it is being changed by the current operation/function
      hist.pop_back();

      // remove 2nd last item from number history if an operation is being used
      if (!token.type) hist.pop_back();

      // evaluate math operation/function and add the resulting number to the number history
      Serial.println(token.math(x, y, isRadians));
      hist.push_back(token.math(x, y, isRadians));

    }
  }

  // return the only element left in the number history, which is the answer.
  return hist[0];

}



void solve() {

//  f() = factorial
//  #() = square root

  arx::deque<Token> stack = shuntingYardConverter(equationString);

  Serial.print("equation in RPN: ");

  for (int i = 0; i < stack.size(); i++) {
    Serial.print("value: ");
    Serial.println(stack[i].value);
    Serial.print("type: ");
    Serial.println(stack[i].type);
    Serial.println();
  }

  Serial.println();


  double solution = shuntingYardEvaluator(stack, isRadians);

//   solution = round(solution);


  Serial.print("solution: ");
  Serial.println(solution);

  equationString += " =";
  numberString = solution;

}



arx::deque<int> binaryConverter(int input) {

  switch (input) {
    case 1: return {0, 0, 0, 1};
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
  return {0};
}


void updateDisplay() {

  arx::vector<char> newEquation;

  for (char i: equationString) newEquation.push_back(i);

  lcd.setCursor(0, 0);

  for (char i: newEquation) lcd.print(i);

  lcd.setCursor(0, 1);

  lcd.print("                ");

  lcd.setCursor(0, 1);

  lcd.print(numberString);

  
}


void decimalRound() {
  
  analogOne = analogRead(A0);

  analogOne = map(analogOne, 0, 1023, 0, 10);

  arx::deque<int> binaryValues = binaryConverter(analogOne);

  digitalWrite(icPins[3], binaryValues[3]);
  digitalWrite(icPins[0], binaryValues[2]);
  digitalWrite(icPins[1], binaryValues[1]);
  digitalWrite(icPins[2], binaryValues[0]);

//   return analogOne;
}


void clearData() {
  equationString = "";
  numberString = "";
}

void serialHandler(String input) {

  equationString += numberString;
  numberString = "";
  
  if (input == "Sine"       || input == "sin")  {equationString += "s("; return;}
  if (input == "Cosine"     || input == "cos")  {equationString += "c("; return;}
  if (input == "Tangent"    || input == "tan")  {equationString += "t("; return;}
  if (input == "ArcSine"    || input == "asin") {equationString += "S("; return;}
  if (input == "ArcCosine"  || input == "acos") {equationString += "C("; return;}
  if (input == "ArcTangent" || input == "atan") {equationString += "T("; return;}
  if (input == "Logarithm"  || input == "log")  {equationString += "l("; return;}
  if (input == "Factorial"  || input == "!")    {equationString += "f("; return;}
  if (input == "SquareRoot" || input == "sqrt") {equationString += "#("; return;}

  if (input == "Exponential"    || input == "^") {equationString += " ^ "; return;}
  if (input == "Modulus"        || input == "%") {equationString += " % "; return;}
  if (input == "Division"       || input == "/") {equationString += " / "; return;}
  if (input == "Multiplication" || input == "*") {equationString += " * "; return;}
  if (input == "Addition"       || input == "+") {equationString += " + "; return;}
  if (input == "Subtraction"    || input == "-") {equationString += " - "; return;}

  if (input == "(") {equationString += "("; return;}
  if (input == ")") {equationString += ")"; return;}

  if (input == "clear") {clearData(); return;}
  if (input == "solve") {solve(); return;}

  if (input == "Radians") {isRadians = true;  Serial.println("mode set to Radians."); return;}
  if (input == "Degrees") {isRadians = false; Serial.println("mode set to Degrees."); return;}
}





void setup() {

  Serial.begin(9600);

  lcd.begin(16, 2);

  makeTokens();

  pinMode(A0, INPUT);

  for (int i: icPins) pinMode(i, OUTPUT);
  


}

void loop() {


//   analogOne = decimalRound();

  decimalRound();

//  String equation = "4+(f(3)*(52+73*#(64)/2_220)_2^(5_2))/15";

  updateDisplay();

  delay(100);

  char key = keypad.getKey();

  if (key) {
    Serial.println(key);
    numberString += String(key);
  }

  if (Serial.available()) {
    String input = Serial.readString();
    serialHandler(input);
    Serial.print("equation: ");
    Serial.println(equationString);
  }

  

  
}
