#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <string>
#include <typeinfo>

using namespace std;



bool LEFT = true;
bool RIGHT = false;

int NUMBER = -1;
int OPERATOR = 0;
int BRACKET = 3;
int FUNCTION = 1;
int COMMA = 5;
int LEFT_BRACKET = 2;
int RIGHT_BRACKET = 3;

string STRINGID = "NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE";








class Token {

    public:

    int type;
    int precedence;
    bool associativity;
    string value;
    double apply;

    Token(int type = 0, int precedence = 0, bool associativity = false, string value = "", double apply = 0.0) {
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




Token getToken(string input) {

    for (Token i : TOKENS) {

        if (i.value == input) {

            return i;

        }
    }

    return Token(NUMBER);

}




void shuntingYardConverter(string equation) {

    vector<string> inStack(equation.begin(), equation.end());
    // vector<Token> opStack;
    // vector<Token> outStack;

    cout << "original vector: ";

    for (string i: inStack) {cout << i;}

    cout << endl;

    int index = 0;
    for (string item: inStack) {

        if (item == "!") {

            inStack[index] = ")";

            for (int i = index; i >= 0; i--) {

                vector<string> characters{"1", "2", "3", "4", "5", "6", "7", "8", "9", "0", ".", "-"};

                if (find(characters.begin(), characters.end(), inStack[i]) != characters.end()) {

                    inStack.insert(inStack.begin() + i, "f");

                    inStack.insert(inStack.begin() + i + 1, "(");

                    break;

                }
            }
        }
        index++;
    }

    cout << "new vector: ";

    for (string i: inStack) {cout << i;}

    // while (inStack.size() > 0) {

    // if (true) {

    //     vector<char> tempStack;


    //     try {

    //         if (typeid(token).name() != STRINGID && token.value != ")") {

    //             string input = inStack.back();

    //             inStack.pop_back();

    //             Token token = getToken(input);

    //         } else if (typeid(token).name() == STRINGID || token.value == ")") {

    //             string input = inStack.back();

    //             inStack.pop_back();

    //             Token token = getToken(input);

    //         } else {throw(69);}

    //     } catch (...) {

    //         string input = inStack.back();

    //         inStack.pop_back();

    //         Token token = getToken(input);

    //     }

    //     cout << "token: " << token.value << endl;

    //     // break;


    //     // after this, if the token is a number, then add the following numbers to an array, convert it to a string, 
    //     // make token a 'Token' and set the value to the string of numbers.

    // }




    // return outStack;

}

double shuntingYardEvaluator(vector<string> equation) {

    equation = equation;

    return 0.0;

}



int main() {



    string equation = "4 + (3! * (52 + 73 * #(64) / 2 _ 220) _  2 ^ (5 _ 2)) / 15";

    string test = "e";

    cout << typeid(equation).name() << endl;

    shuntingYardConverter(equation);



    // cout << "output: " << output << endl;


}


// string numberOutput;
// Token tokenOutput;

// string input = "16";

// getToken(input, &numberOutput, &tokenOutput);

// if (numberOutput == input) {

//     string token = numberOutput;

//     cout << "output: " << token;

// } else {

//     Token token = tokenOutput;

//     cout << "output: " << token.value << endl;

// }
