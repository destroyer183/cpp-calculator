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



double math(std::string name, double x, double y) {

    std::deque<std::string> characters{"s", "c", "t", "S", "C", "T"};

    // converting degrees to radians
    if (find(characters.begin(), characters.end(), name) != characters.end()) x = x*3.14159/180;

    if (name == "s") return sin(x);
    if (name == "c") return cos(x);
    if (name == "t") return tan(x);
    if (name == "S") return tan(x);
    if (name == "C") return tan(x);
    if (name == "T") return tan(x);
    if (name == "l") return log(x);
    if (name == "f") return tgamma(x + 1);
    if (name == "#") return sqrt(x);

    if (name == "^") return pow(x, y);
    if (name == "%") {int x1 = int (x); int y1 = int (y); return x1 % y1;}
    if (name == "/") return x / y;
    if (name == "*") return x * y;
    if (name == "+") return x + y;
    if (name == "_") return x - y;

    return 0.0;
}



class Token {

    public:

        int type;
        int precedence;
        bool associativity;
        std::string value;
        double (*apply)(std::__cxx11::basic_string<char>, double, double);

        Token(int typee = 0, int precedencee = 0, bool associativitye = false, std::string valuee = "", double (*applye)(std::__cxx11::basic_string<char>, double, double) = math) {
            type = typee;
            precedence = precedencee;
            associativity = associativitye;
            value = valuee;
            apply = applye;
        }
};



std::deque<Token> TOKENS;

void makeTokens() {

    TOKENS.push_back(Token(FUNCTION, 5, LEFT, "s", math));
    TOKENS.push_back(Token(FUNCTION, 5, LEFT, "c", math));
    TOKENS.push_back(Token(FUNCTION, 5, LEFT, "t", math));
    TOKENS.push_back(Token(FUNCTION, 5, LEFT, "S", math));
    TOKENS.push_back(Token(FUNCTION, 5, LEFT, "C", math));
    TOKENS.push_back(Token(FUNCTION, 5, LEFT, "T", math));
    TOKENS.push_back(Token(FUNCTION, 5, LEFT, "l", math));
    TOKENS.push_back(Token(FUNCTION, 4, LEFT, "f", math));
    TOKENS.push_back(Token(FUNCTION, 2, LEFT, "#", math));

    TOKENS.push_back(Token(OPERATOR, 3, RIGHT, "^", math));
    TOKENS.push_back(Token(OPERATOR, 1, LEFT,  "%", math));
    TOKENS.push_back(Token(OPERATOR, 1, LEFT,  "/", math));
    TOKENS.push_back(Token(OPERATOR, 1, LEFT,  "*", math));
    TOKENS.push_back(Token(OPERATOR, 0, LEFT,  "+", math));
    TOKENS.push_back(Token(OPERATOR, 0, LEFT,  "_", math));

    TOKENS.push_back(Token(LEFT_BRACKET,  0, RIGHT, "(", math));
    TOKENS.push_back(Token(RIGHT_BRACKET, 0, LEFT,  ")", math));

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

            hist.push_back(i.apply(i.value, x, y));

        }
    }

    return hist.at(0);

}



int main() {

    makeTokens();

    Token token = TOKENS[0];

    std::cout << "test: " << token.apply(token.value, 60, 0) << std::endl;

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

