#include <iostream>
#include <vector>

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

    vector<string> inStack; // should be a list of equation

    equation = equation;

    return equation;

}

double shuntingYardEvaluator(string equation) {

    equation = equation;

    return 0.0;

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


int main() {





    string equation = "4 + (3! * (52 + 73 * #(64) / 2 _ 220) _  2 ^ (5 _ 2)) / 15";

    double output = shuntingYardEvaluator(equation);

    cout << "output: " << output << endl;


}

