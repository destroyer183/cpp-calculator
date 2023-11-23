#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <string>

using namespace std;



bool LEFT = true;
bool RIGHT = false;

int NUMBER = 0;
int OPERATOR = 0;
int BRACKET = 3;
int FUNCTION = 1;
int COMMA = 5;
int LEFT_BRACKET = 2;
int RIGHT_BRACKET = 3;



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
    Token(OPERATOR, 0, LEFT,  "-", 4.4),

    Token(LEFT_BRACKET,  0, RIGHT, "(", 0.0),
    Token(RIGHT_BRACKET, 0, LEFT,  ")", 0.0)

};




void getToken(string input, string *value, Token *token) {

    for (Token i : TOKENS) {

        if (i.value == input) {

            *token = i;

        }
    }
    *value = input;
}






string shuntingYardConverter(string equation) {

    vector<char> inStack(equation.begin(), equation.end());
    vector<char> opStack;
    vector<char> outStack;

    cout << "original vector: ";

    for (char i: inStack) {cout << i;}

    cout << endl;

    int index = 0;
    for (char item: inStack) {

        if (item == '!') {

            inStack[index] = ')';

            for (int i = index; i >= 0; i--) {

                vector<char> characters{'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '.', '-'};

                if (find(characters.begin(), characters.end(), inStack[i]) != characters.end()) {

                    inStack.insert(inStack.begin() + i, 'f');

                    inStack.insert(inStack.begin() + i + 1, '(');

                    break;

                }
            }
        }
        index++;
    }

    cout << "new vector: ";

    for (char i: inStack) {cout << i;}






    return equation;

}

double shuntingYardEvaluator(string equation) {

    equation = equation;

    return 0.0;

}



int main() {



    string equation = "4 + (3! * (52 + 73 * #(64) / 2 _ 220) _  2 ^ (5 _ 2)) / 15";

    shuntingYardConverter(equation);

    // cout << "output: " << output << endl;


}


// string valueOutput;
// Token tokenOutput;

// string input = "16";

// getToken(input, &valueOutput, &tokenOutput);

// if (valueOutput == input) {

//     string token = valueOutput;

//     cout << "output: " << token;

// } else {

//     Token token = tokenOutput;

//     cout << "output: " << token.value << endl;

// }
