#include <iostream>
#include <deque>
#include <bits/stdc++.h>
#include <string>
#include "calc.h"
#include "token.h"
#include "stringToDouble.h"


// make macro to improve syntax for making a new token
#define defineToken(type, precedence, associativity, value, operation) TOKENS.push_back(Token(type, precedence, associativity, value, operation))

// make macro to reuse code for removing element from one array and putting it on another
#define popAppend(temp, popStack, appendStack) ({\
    temp = popStack.back();\
    appendStack.push_back(temp);\
    popStack.pop_back();\
    })


// declare array to hold tokens
std::deque<Token> TOKENS;


// fill array with tokens that represent mathematical operators and functions
void makeTokens() {

    defineToken(FUNCTION, 5, LEFT, "s", Sine);
    defineToken(FUNCTION, 5, LEFT, "c", Cosine);
    defineToken(FUNCTION, 5, LEFT, "t", Tangent);
    defineToken(FUNCTION, 5, LEFT, "S", aSine);
    defineToken(FUNCTION, 5, LEFT, "C", aCosine);
    defineToken(FUNCTION, 5, LEFT, "T", aTangent);
    defineToken(FUNCTION, 5, LEFT, "l", Logarithm);
    defineToken(FUNCTION, 4, LEFT, "f", Factorial);
    defineToken(FUNCTION, 2, LEFT, "#", SquareRoot);

    defineToken(OPERATOR, 3, RIGHT, "^", Exponential);
    defineToken(OPERATOR, 1, LEFT,  "%", Modulo);
    defineToken(OPERATOR, 1, LEFT,  "/", Division);
    defineToken(OPERATOR, 1, LEFT,  "*", Multiplication);
    defineToken(OPERATOR, 0, LEFT,  "+", Addition);
    defineToken(OPERATOR, 0, LEFT,  "_", Subtraction);

    defineToken(LEFT_BRACKET,  0, RIGHT, "(", Null);
    defineToken(RIGHT_BRACKET, 0, LEFT,  ")", Null);

}



// function to either return a token that already exists, or make a new one for a number.
Token getToken(std::string input) {

    std::cout << "input: " << input << std::endl;

    // loop through all math tokens
    for (Token i : TOKENS) {

        // check if inputted value is equal to any existing tokens
        if (i.value == input) {

            std::cout << "token set: " << i.value << std::endl;

            // return matching existing token
            return i;

        }
    }

    // declare new token
    Token temp;
     
    // set attributes of new token
    temp.type = NUMBER;
    temp.precedence = 0;
    temp.associativity = LEFT;
    temp.value = input;

    std::cout << "number set: " << temp.value << std::endl;

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
std::deque<Token> shuntingYardConverter(std::string equation) {

    std::deque<std::string> inStack; // declare input stack
    std::deque<Token> opStack; // declare operator stack
    std::deque<Token> outStack; // declare output stack
    std::deque<std::string> tempStack; // declare temporary stack
    std::deque<std::string> characters{"1", "2", "3", "4", "5", "6", "7", "8", "9", "0", ".", "-"}; // define characters for searching for a number

    // declare main token and temporary token
    Token token;
    Token temp;

    // declare variables to hold temporary data for creating numbers
    std::string nums;
    std::string input;

    std::cout << "size: " << inStack.size() << std::endl;

    // add every element from input to the input array
    for (char c: equation) inStack.push_back(std::string(1, c));

    std::cout << "original deque: ";

    for (std::string i: inStack) {std::cout << i;}

    std::cout << std::endl;

    // for loop to change syntax of factorials
    for (int index = 0; index < inStack.size(); index++) {

        // check if element is an exclamation point (factorial)
        if (inStack[index] == "!") {

            // change element to right bracket
            inStack[index] = ")";

            // for loop to find the beginning of number by looping backwards over every character before factorial symbol
            // this will change the syntax to a function like sin(x)
            for (int i = index; i >= 0; i--) {

                // check if current character is not a number
                if (find(characters.begin(), characters.end(), inStack[i]) == characters.end()) {

                    // insert 'f' at index where number ends
                    inStack.insert(inStack.begin() + i - 1, "f");

                    // insert left bracket where number ends
                    inStack.insert(inStack.begin() + i, "(");

                    // exit loop
                    break;

                }
            }
        }
    }

    std::cout << "new deque: ";

    for (std::string i: inStack) {std::cout << i;}

    std::cout << std::endl;

    // while loop to keep looping over input stack until every element has been removed from it
    while (inStack.size() > 0 && inStack.size() < 1000) {

        // define temporary array as empty array
        tempStack = {};

        // create new token from first element of input array
        newToken(input, inStack, token);

        // skip loop if token is a whitespace
        if (token.value == " ") continue;

        // check if the new token is a number
        if (token.type == NUMBER) {

            // check if token value is a character that belongs in a number
            if (find(characters.begin(), characters.end(), token.value) != characters.end()) {

                // try/catch exception handling to avoid crashes
                try {

                    // keep looping until first element of input stack is not a character that belongs in a number
                    while (find(characters.begin(), characters.end(), token.value) != characters.end()) {

                        std::cout << "number found" << std::endl << std::endl;

                        // add numbertoken to temporary stack
                        tempStack.push_back(token.value);

                        // check if inpust stack is not empty
                        if (inStack.size() > 0) {

                            // remove first element of input stack and make it a token
                            newToken(input, inStack, token);

                        // exit loop if input stack is empty
                        } else break;

                    }
                // don't do anything if while loop errors
                } catch (...) {}

                // define placeholder string as emptry string
                nums = "";

                // loop through every digit in temporary stack and add it to placeholder string
                for (std::string i : tempStack) {nums += i;}

                std::cout << "new number: " << nums << std::endl << "token.type: " << -1 << std::endl << std::endl;

                // make placeholder string a token and assign it to placeholder token
                temp = getToken(nums);

                // add new token to output stack
                outStack.push_back(temp);
            }

        }

        // try/catch exception handling to avoid crashes
        try {

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



        // don't do anything if there is an error
        } catch (...) {}


    }



    // remove every element from operator stack and put them on the output stack
    while (opStack.size() > 0) popAppend(temp, opStack, outStack);

    
    std::cout << "equation in RPN: ";

    for (Token i : outStack) std::cout << i.value << " ";

    std::cout << std::endl;

    // return output stack
    return outStack;
}


// function to find the numbers needed for a math operation/function
std::vector<double> findNumbers(tokenType type, std::deque<double> hist) {

    // only return one number from the end of the number history if it is for a function, and return a 0
    if (type == FUNCTION) return std::vector<double> {hist.at(hist.size() - 1), 0.0};

    // return two numbers from the end of the number history if it is for an operation
    else if (type == OPERATOR) return std::vector<double> {hist.at(hist.size() - 2), hist.back()};

    // return two zeroes if neither if statement triggers, this should never happen
    return std::vector<double> {0.0, 0.0};
}



// main function for evaluating and solving equation once it is in reverse polish notation
double shuntingYardEvaluator(std::deque<Token> equation, bool isRadians) {

    // define variable to hold inputted equation
    std::deque<Token> stack = equation;

    // define empty array to hold numbers
    std::deque<double> hist = {};

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
            std::vector<double> arr = findNumbers(token.type, hist);

            // make two variable hold the two necessary numbers
            double x = arr.at(0);
            double y = arr.at(1);

            std::cout << "num1: " << x << std::endl << "num2: " << y << std::endl << "operation: " << token.value << std::endl;

            // remove last element from number history, since it is being changed by the current operation/function
            hist.pop_back();
            
            // remove 2nd last item from number history if an operation is being used
            if (!token.type) hist.pop_back();

            // evaluate math operation/function and add the resulting number to the number history
            hist.push_back(token.math(x, y, isRadians));

        }
    }

    // return the only element left in the number history, which is the answer.
    return hist.at(0);

}



int main() {

    makeTokens();

    Token token = TOKENS[0];

    bool isRadians = false;

    std::cout << "test: " << token.math(60, 0, isRadians) << std::endl;

    std::string equation = "4 + (3! * (52 + 73 * #(64) / 2 _ 220) _  2 ^ (5 _ 2)) / 15";

    // equation = "s(60)";



    std::deque<Token> stack = shuntingYardConverter(equation);

    std::cout << "equation in RPN: ";
    for (Token i : stack) {
        std::cout << "value: " << i.value << std::endl << "type: " << i.type << std::endl << std::endl;
    }
    std::cout << std::endl;


    double solution = shuntingYardEvaluator(stack, isRadians);

    std::cout << "solution: " << solution << std::endl;

}