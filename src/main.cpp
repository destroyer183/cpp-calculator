#include <iostream>
#include <deque>
#include <bits/stdc++.h>
#include <string>
#include <string.h>



const bool LEFT = true;
const bool RIGHT = false;

const int NUMBER = -1;
const int OPERATOR = 0;
const int BRACKET = 3;
const int FUNCTION = 1;
const int COMMA = 5;
const int LEFT_BRACKET = 2;
const int RIGHT_BRACKET = 3;



enum MathOperation {
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
    null
};



class Token {

    public:

        int type;
        int precedence;
        bool associativity;
        std::string value;
        MathOperation apply;

        Token(int typee = 0, int precedencee = 0, bool associativitye = false, std::string valuee = "", MathOperation applye = null) {
            type = typee;
            precedence = precedencee;
            associativity = associativitye;
            value = valuee;
            apply = applye;
        }

        double math(MathOperation operation, double x, double y) {

            std::deque<MathOperation> characters{Sine, Cosine, Tangent, aSine, aCosine, aTangent};

            // converting degrees to radians
            if (find(characters.begin(), characters.end(), operation) != characters.end()) x = x*3.14159/180;

            switch (operation) {
                case Sine:       return sin(x);
                case Cosine:     return cos(x);
                case Tangent:    return tan(x);
                case aSine:      return asin(x);
                case aCosine:    return acos(x);
                case aTangent:   return atan(x);
                case Logarithm:  return log(x);
                case Factorial:  return tgamma(x + 1);
                case SquareRoot: return sqrt(x);

                case Exponential:    return pow(x, y);
                case Modulo: {int x1 = int (x); int y1 = int (y); return x1 % y1;}
                case Division:       return x / y;
                case Multiplication: return x * y;
                case Addition:       return x + y;
                case Subtraction:    return x - y;
                case null: std::cout << "well fuck, there is a bug." << std::endl;

            }
            return 0.0;
        }
};



std::deque<Token> TOKENS;

void makeTokens() {

    TOKENS.push_back(Token(FUNCTION, 5, LEFT, "s", Sine));
    TOKENS.push_back(Token(FUNCTION, 5, LEFT, "c", Cosine));
    TOKENS.push_back(Token(FUNCTION, 5, LEFT, "t", Tangent));
    TOKENS.push_back(Token(FUNCTION, 5, LEFT, "S", aSine));
    TOKENS.push_back(Token(FUNCTION, 5, LEFT, "C", aCosine));
    TOKENS.push_back(Token(FUNCTION, 5, LEFT, "T", aTangent));
    TOKENS.push_back(Token(FUNCTION, 5, LEFT, "l", Logarithm));
    TOKENS.push_back(Token(FUNCTION, 4, LEFT, "f", Factorial));
    TOKENS.push_back(Token(FUNCTION, 2, LEFT, "#", SquareRoot));

    TOKENS.push_back(Token(OPERATOR, 3, RIGHT, "^", Exponential));
    TOKENS.push_back(Token(OPERATOR, 1, LEFT,  "%", Modulo));
    TOKENS.push_back(Token(OPERATOR, 1, LEFT,  "/", Division));
    TOKENS.push_back(Token(OPERATOR, 1, LEFT,  "*", Multiplication));
    TOKENS.push_back(Token(OPERATOR, 0, LEFT,  "+", Addition));
    TOKENS.push_back(Token(OPERATOR, 0, LEFT,  "_", Subtraction));

    TOKENS.push_back(Token(LEFT_BRACKET,  0, RIGHT, "(", null));
    TOKENS.push_back(Token(RIGHT_BRACKET, 0, LEFT,  ")", null));

}



int getToken(std::string input, Token *token) {

    std::cout << "input: " << input << std::endl;

    for (Token i : TOKENS) {

        if (i.value == input) {

            Token temp;

            temp.type = i.type;
            temp.precedence = i.precedence;
            temp.associativity = i.associativity;
            temp.value = i.value;
            temp.apply = i.apply;

            *token = temp;

            std::cout << "token set: " << temp.value << std::endl;

            return 0;

        }
    }

    Token temp;
     
    temp.type = NUMBER;
    temp.precedence = 0;
    temp.associativity = LEFT;
    temp.value = input;

    *token = temp;

    std::cout << "number set: " << temp.value << std::endl;

    return 0;

}




std::deque<Token> shuntingYardConverter(std::string equation) {

    std::deque<std::string> inStack;
    std::deque<Token> opStack;
    std::deque<Token> outStack;
    std::deque<std::string> tempStack;
    std::deque<std::string> characters{"1", "2", "3", "4", "5", "6", "7", "8", "9", "0", ".", "-"};

    int index = 0;

    Token token;
    Token temp;

    std::string nums;
    std::string input;

    std::cout << "size: " << inStack.size() << std::endl;

    for (char c: equation) {inStack.push_back(std::string(1, c));}

    std::cout << "original deque: ";

    for (std::string i: inStack) {std::cout << i;}

    std::cout << std::endl;


    for (std::string item: inStack) {

        if (item == "!") {

            inStack[index] = ")";

            for (int i = index; i >= 0; i--) {

                if (find(characters.begin(), characters.end(), inStack[i]) == characters.end()) {

                    inStack.insert(inStack.begin() + i - 1, "f");

                    inStack.insert(inStack.begin() + i, "(");

                    break;

                }
            }
        }
        index++;
    }

    std::cout << "new deque: ";

    for (std::string i: inStack) {std::cout << i;}

    std::cout << std::endl;

    while (inStack.size() > 0 && inStack.size() < 1000) {

        tempStack = {};

        try {

            if (token.value != ")") {

                input = inStack.front();

                inStack.pop_front();

                getToken(input, &token);

                std::cout << "token.value: " << token.value << std::endl << "token.type: " << token.type << std::endl << std::endl;

            } else if (token.value == ")") {

                input = inStack.front();

                inStack.pop_front();

                getToken(input, &token);

                std::cout << "token.value: " << token.value << std::endl << "token.type: " << token.type << std::endl << std::endl;

            } else {throw(69);}

        } catch (...) {

            input = inStack.front();

            inStack.pop_front();

            getToken(input, &token);

            std::cout << "token.value: " << token.value << std::endl << "token.type: " << token.type << std::endl << std::endl;

        }



        if (token.value == " ") {continue;}

        if (token.type == NUMBER) {

            if (find(characters.begin(), characters.end(), token.value) != characters.end()) {

                try {

                    while (find(characters.begin(), characters.end(), token.value) != characters.end()) {

                        std::cout << "number found" << std::endl << std::endl;

                        tempStack.push_back(token.value);

                        if (inStack.size() > 0) {

                            input = inStack.front();

                            inStack.pop_front();

                            getToken(input, &token);

                        } else {break;}

                    }
                } catch (...) {}

                nums = "";

                for (std::string i : tempStack) {nums += i;}

                // token.value = nums; // the token is already a new token, and not 3 any more.

                std::cout << "new number: " << nums << std::endl << "token.type: " << -1 << std::endl << std::endl;

                getToken(nums, &temp);

                outStack.push_back(temp);
            }

        }

        try {

            if (token.type == FUNCTION) {

                opStack.push_back(token);

            }



            else if (token.type == OPERATOR) {

                while (opStack.size() > 0 && opStack.back().value != "(" && (
                    opStack.back().precedence > token.precedence || (
                    opStack.back().precedence == token.precedence &&
                    token.associativity))) {
                        
                        temp = opStack.back();

                        outStack.push_back(temp);

                        opStack.pop_back();

                    }

                opStack.push_back(token);

            }



            else if (token.type == LEFT_BRACKET) {

                opStack.push_back(token);

            }



            else if (token.type == RIGHT_BRACKET) {

                while (opStack.size() > 0 && opStack.back().type != LEFT_BRACKET) {

                    temp = opStack.back();

                    outStack.push_back(temp);

                    opStack.pop_back();

                }
                opStack.pop_back();
            }



        } catch (...) {}


    }



    while (opStack.size() > 0) {
        temp = opStack.back();
        outStack.push_back(temp);
        opStack.pop_back();
    }

    
    std::cout << "equation in RPN: ";
    for (Token i : outStack) {
        std::cout << i.value << " ";   
    }
    std::cout << std::endl;

    return outStack;

}

std::vector<double> findNumbers(int type, std::deque<double> hist) {

    if (type) return std::vector<double> {hist.at(hist.size() - 1), 0.0};

    else return std::vector<double> {hist.at(hist.size() - 2), hist.back()};

    return std::vector<double> {0.0, 0.0};
}

double shuntingYardEvaluator(std::deque<Token> equation) {

    std::deque<Token> stack = equation;

    std::deque<double> hist = {};

    while (stack.size() > 0 && stack.size() < 10000) {

        Token i = stack.front();
        stack.pop_front();

        if (i.type == NUMBER) hist.push_back(std::stod(i.value));

        else {

            std::vector<double> arr = findNumbers(i.type, hist);

            double x = arr.at(0);
            double y = arr.at(1);

            std::cout << "num1: " << x << std::endl << "num2: " << y << std::endl << "apply: " << i.value << std::endl;

            hist.pop_back();
            if (!i.type) hist.pop_back();

            hist.push_back(i.math(i.apply, x, y));

        }
    }

    return hist.at(0);

}



int main() {

    makeTokens();

    Token token = TOKENS[0];

    std::cout << "test: " << token.math(token.apply, 60, 0) << std::endl;

    std::string equation = "4 + (3! * (52 + 73 * #(64) / 2 _ 220) _  2 ^ (5 _ 2)) / 15";

    std::deque<Token> stack = shuntingYardConverter(equation);




    std::cout << "equation in RPN: ";
    for (Token i : stack) {
        std::cout << "value: " << i.value << std::endl << "type: " << i.type << std::endl << std::endl;
    }
    std::cout << std::endl;



    double solution = shuntingYardEvaluator(stack);



    std::cout << "solution: " << solution << std::endl;



    // std::cout << "output: " << output << std::endl;


}

