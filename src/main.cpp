#include <iostream>
#include <deque>
#include <bits/stdc++.h>
#include <string>
#include <typeinfo>



bool LEFT = true;
bool RIGHT = false;

int NUMBER = -1;
int OPERATOR = 0;
int BRACKET = 3;
int FUNCTION = 1;
int COMMA = 5;
int LEFT_BRACKET = 2;
int RIGHT_BRACKET = 3;



std::string STRINGID = "NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE";



class Token {

    public:

    int type;
    int precedence;
    bool associativity;
    std::string value;
    double apply;

    Token(int type = 0, int precedence = 0, bool associativity = false, std::string value = "", double apply = 0.0) {
        type = type;
        precedence = precedence;
        associativity = associativity;
        value = value;
        apply = apply;
    }
    

};



Token token;



Token TOKENS[17] = {

    Token(FUNCTION, 5, LEFT, "s", 4.4),
    Token(FUNCTION, 5, LEFT, "c", 4.4),
    Token(FUNCTION, 5, LEFT, "t", 4.4),
    Token(FUNCTION, 5, LEFT, "S", 4.4),
    Token(FUNCTION, 5, LEFT, "C", 4.4),
    Token(FUNCTION, 5, LEFT, "T", 4.4),
    Token(FUNCTION, 5, LEFT, "l", 4.4),
    Token(FUNCTION, 4, LEFT, "f", 4.4),
    Token(FUNCTION, 2, LEFT, "#", 4.4),

    Token(OPERATOR, 3, RIGHT, "^", 4.4),
    Token(OPERATOR, 1, LEFT,  "%", 4.4),
    Token(OPERATOR, 1, LEFT,  "/", 4.4),
    Token(OPERATOR, 1, LEFT,  "*", 4.4),
    Token(OPERATOR, 0, LEFT,  "+", 4.4),
    Token(OPERATOR, 0, LEFT,  "_", 4.4),

    Token(LEFT_BRACKET,  0, RIGHT, "(", 0.0),
    Token(RIGHT_BRACKET, 0, LEFT,  ")", 0.0)

};




int getToken(std::string input, Token *token) {

    for (Token i : TOKENS) {

        if (i.value == input) {

            *token = i;

            return 0;

        }
    }

    Token temp;
     
    temp.type = NUMBER;
    temp.precedence = 0;
    temp.associativity = LEFT;
    temp.value = input;
    temp.apply = 0.0;

    *token = temp;

    return 0;

}




std::deque<Token> shuntingYardConverter(std::string equation) {

    std::deque<std::string> inStack;
    std::deque<Token> opStack;
    std::deque<Token> outStack;

    for (char c: equation) {inStack.push_back(std::string(1, c));}

    std::cout << "original deque: ";

    for (std::string i: inStack) {std::cout << i;}

    std::cout << std::endl;

    int index = 0;

    for (std::string item: inStack) {

        if (item == "!") {

            inStack[index] = ")";

            for (int i = index; i >= 0; i--) {

                std::deque<std::string> characters{"1", "2", "3", "4", "5", "6", "7", "8", "9", "0", ".", "-"};

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

    while (inStack.size() > 0) {

        std::deque<std::string> tempStack;

        try {

            if (typeid(token).name() != STRINGID && token.value != ")") {

                std::string input = inStack.front();

                inStack.pop_front();

                getToken(input, &token);

                std::cout << "token.type: " << token.type << std::endl << "token.value: " << token.value << std::endl;

            } else if (typeid(token).name() == STRINGID || token.value == ")") {

                std::string input = inStack.front();

                inStack.pop_front();

                getToken(input, &token);

                std::cout << "token.type: " << token.type << std::endl << "token.value: " << token.value << std::endl;

            } else {throw(69);}

        } catch (...) {

            std::string input = inStack.front();

            inStack.pop_front();

            getToken(input, &token);

            std::cout << "token.type: " << token.type << std::endl << "token.value: " << token.value << std::endl;

        }



        if (token.value == " ") {continue;}

        if (token.type == NUMBER) {

            std::cout << "yes" << std::endl;

            std::deque<std::string> characters{"1", "2", "3", "4", "5", "6", "7", "8", "9", "0", ".", "-"};

            if (find(characters.begin(), characters.end(), token.value) != characters.end()) {

                try {

                    while (find(characters.begin(), characters.end(), token.value) != characters.end()) {

                        tempStack.push_back(token.value);

                        std::string input = inStack.front();

                        inStack.pop_front();

                        getToken(input, &token);

                    }
                } catch (...) {}

                std::string nums;

                for (std::string i : tempStack) {nums += i;}

                token.value = nums;

                std::cout << "token.value: " << token.value << std::endl;
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
                        
                        Token temp = opStack.back();

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

                    Token temp = opStack.back();

                    outStack.push_back(temp);

                    opStack.pop_back();

                }
            }



        } catch (...) {}

        std::cout << "bruh: " << inStack.size() << std::endl;



    }

    std::cout << "hello?" << std::endl;


    while (opStack.size() > 0) {
        Token temp = opStack.back();
        outStack.push_back(temp);
        opStack.pop_back();
    }

    
    std::cout << "equation in RPN: ";
    for (Token i : outStack) {
        std::cout << i.value;
    }

    return outStack;

}

double shuntingYardEvaluator(std::deque<std::string> equation) {

    equation = equation;

    return 0.0;

}



int main() {



    std::string equation = "44 + (3! * (52 + 73 * #(64) / 2 _ 220) _  2 ^ (5 _ 2)) / 15";

    std::string test = "e";

    std::cout << typeid(equation).name() << std::endl;

    std::deque<Token> stack = shuntingYardConverter(equation);


    std::cout << "equation in RPN: ";
    for (Token i : stack) {
        std::cout << i.value;
    }



    // std::cout << "output: " << output << std::endl;


}

