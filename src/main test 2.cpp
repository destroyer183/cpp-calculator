#include <iostream>
#include <deque>
#include <bits/stdc++.h>
#include <string>
#include <string.h>
#include <cstddef>
#include <cstring>
#define PI 3.14159265358979323846
#define degreesToRadians(degrees) (((degrees) * (PI)) / 180.0)
#define radiansToDegrees(radians) (((radians) * 180) / (PI))
#define defineToken(type, precedence, associativity, value, apply) TOKENS.push_back(Token(type, precedence, associativity, value, apply))
#define popAppend(temp, popStack, appendStack) ({\
    temp = popStack.back();\
    appendStack.push_back(temp);\
    popStack.pop_back();\
    })



#define I_declareth int
#define to_be_equivalent_to =
#define my_good_sir ;

I_declareth x to_be_equivalent_to 3 my_good_sir



const bool LEFT = true;
const bool RIGHT = false;

const int NUMBER = -1;
const int OPERATOR = 0;
const int BRACKET = 3;
const int FUNCTION = 1;
const int COMMA = 5;
const int LEFT_BRACKET = 2;
const int RIGHT_BRACKET = 3;


template <typename T>
class Vector
{
private:
  size_t size;     // Number of elements in the vector
  size_t capacity; // Capacity of the array
  T *array;        // Dynamic array to store elements

public:
    Vector(size_t initialSize = 0)
  {

    size = 0;
    capacity = initialSize;

    if (capacity == 0)
    {
      capacity = 10;
    }

    array = new T[capacity];
  }

  ~Vector()
  {
    if (!array)
      return;
    delete[] array;
  }

  T &operator[](size_t index) { return array[index]; }

  size_t getSize() const { return size; }

  T front() const { return array[0]; }

  T back() { return array[size - 1]; }

  void double_size()
  {

    capacity = capacity * 2 + 1;

    T *newArray = new T[capacity];

    std::memcpy(newArray, array, size * sizeof(T));

    delete[] array;
    array = newArray;
  }

  void push_back(const T &value)
  {

    if (size == capacity)
    {
      double_size();
    }

    array[size] = value;
    ++size;
  }

  void pop_front()
  {

    if (size == 0)
    {
      return;
    }

    if (size == 1)
    {
      --size;
      return;
    }

    std::memmove(array, array + 1, (size - 1) * sizeof(T));

    --size;
  }

  void pop_back()
  {

    if (size == 0)
    {
      return;
    }

    --size;
  }

  bool pop(size_t index, T *outvalue)
  {

    if (index >= size || outvalue == nullptr)
    {
      return false;
    }

    *outvalue = array[index];

    if (index == 0)
    {
      pop_front();
      return true;
    }

    if (index == size - 1)
    {
      pop_back();
      return true;
    }

    std::memmove(array + index, array + index + 1,
                 (size - index - 1) * sizeof(T));

    --size;
    return true;
  }

  void insert(int index, const T &value)
  {

    if (index == size)
    {
      push_back(value);
      return;
    }

    if (size == capacity)
    {
      double_size();
    }

    std::memmove(array + index + 1, array + index,
                 (size - index) * sizeof(T));

    array[index] = value;
    ++size;
  }

  int find(T value)
  {

    for (size_t i = 0; i < size; ++i)
    {
      if (array[i] == value)
        return i;
    }

    return -1;
  }

    int rfind(T value)
    {

        for (size_t i = size; i > 0; --i)
        {
          if (array[i] == value)
            return i;
        }

        return -1;
    }

    void printStack() {

        std::cout << "stack: ";

        for (size_t i = 0; i < size; ++i) {
            std::cout << array[i].value << " ";
        }

        std::cout << std::endl;
    }

    void print_stack() {

        std::cout << "stack: ";

        for (size_t i = 0; i < size; ++i) {
            std::cout << array[i] << " ";
        }

        std::cout << std::endl;
    }
};

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

    double math(MathOperation operation, double x, double y, bool isRadians) {

        switch (operation) {
            case Sine:       if (isRadians) return sin(x); else return sin(degreesToRadians(x));
            case Cosine:     if (isRadians) return cos(x); else return cos(degreesToRadians(x));
            case Tangent:    if (isRadians) return tan(x); else return tan(degreesToRadians(x));
            case aSine:      if (isRadians) return asin(x); else return asin(radiansToDegrees(x));
            case aCosine:    if (isRadians) return acos(x); else return acos(radiansToDegrees(x));
            case aTangent:   if (isRadians) return atan(x); else return atan(radiansToDegrees(x));
            case Logarithm:  return log(x);
            case Factorial:  return tgamma(x + 1);
            case SquareRoot: return sqrt(x);

            case Exponential:    return pow(x, y);
            case Modulo: {int x1 = int (x); int y1 = int (y); return x1 % y1;}
            case Division:       return x / y;
            case Multiplication: return x * y;
            case Addition:       return x + y;
            case Subtraction:    return x - y;

            case null: std::cout << "well shit, there is a bug." << std::endl;

        }
        return 0.0;
    }

    Token &operator=(const Token &other) {
        if (this != &other) {
            this->type = other.type;
            this->precedence = other.precedence;
            this->associativity = other.associativity;
            this->value.assign(other.value);
            this->apply = other.apply;
        }
        return *this;
    }

    Token &operator=(Token &&other) noexcept {

        if (this != &other) {
            this->type = other.type;
            this->precedence = other.precedence;
            this->associativity = other.associativity;
            this->value.assign(other.value);
            this->apply = other.apply;
        }
        return *this;
    }
};



Vector<Token> TOKENS;

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

    defineToken(LEFT_BRACKET,  0, RIGHT, "(", null);
    defineToken(RIGHT_BRACKET, 0, LEFT,  ")", null);

}



int getToken(std::string input, Token *token) {

    std::cout << "input: " << input << std::endl;

    for (size_t i = 0; i < TOKENS.getSize(); ++i) { 

        if (TOKENS[i].value == input) {
            
            *token = TOKENS[i];

            std::cout << "token set: " << TOKENS[i].value << std::endl;

            return 0;

        }
    }

    Token temp;
     
    temp.type = NUMBER;
    temp.precedence = 0;
    temp.associativity = LEFT;
    temp.value = input;

    *token = temp;

    std::cout << "number set: \'" << temp.value << "\'" << std::endl;

    return 0;

}

#define printStacks() ({\
    std::cout << std::endl;\
    inStack.print_stack();\
    opStack.printStack();\
    outStack.printStack();\
})

#define newToken(input, stack, token) ({\
    input = inStack.front();\
    stack.pop_front();\
    printStacks();\
    getToken(input, &token);\
})




Vector<Token> shuntingYardConverter(std::string equation) {

    Vector<std::string> inStack;
    Vector<Token> opStack;
    Vector<Token> outStack;
    Vector<std::string> tempStack;
    std::string chars = "1234567890.-";
    Vector<std::string> characters;

    for (char i : chars) characters.push_back(std::string(1, i));

    int index = 0;

    Token token;
    Token temp;

    std::string nums;
    std::string input;

    std::cout << "size: " << inStack.getSize() << std::endl;

    for (char c: equation) inStack.push_back(std::string(1, c));

    std::cout << "original deque: ";

    for (size_t i = 0; i < inStack.getSize(); ++i) std::cout << inStack[i];

    std::cout << std::endl;


    for (size_t i = 0; i < inStack.getSize(); ++i) {

        if (inStack[i] == "!") {

            inStack[index] = ")";

            for (int i = index; i >= 0; i--) {

                if (characters.find(inStack[i]) == -1) {

                    inStack.insert(i - 1, "f");

                    inStack.insert(i, "(");

                    break;

                }
            }
        }
        index++;
    }

    std::cout << "new deque: ";

    for (size_t i = 0; i < inStack.getSize(); ++i) std::cout << inStack[i];

    std::cout << std::endl;

    while (inStack.getSize() > 0 && inStack.getSize() < 1000) {

        tempStack = {};

        newToken(input, inStack, token);

        if (token.value == " ") continue;

        if (token.type == NUMBER) {

            if (characters.find(token.value) != -1) {

                try {

                    while (characters.find(token.value) != -1) {

                        std::cout << "number found: " << token.value << std::endl << std::endl;

                        tempStack.push_back(token.value);

                        if (inStack.getSize() > 0) {

                            newToken(input, inStack, token);

                            

                        } else {break;}

                    }
                } catch (...) {}

                nums = "";

                for (size_t i = 0; i < tempStack.getSize(); ++i) nums += tempStack[i];

                std::cout << "new number: " << nums << std::endl << "token.type: " << -1 << std::endl << std::endl;

                getToken(nums, &temp);

                outStack.push_back(temp);

                printStacks();

            }

        }

        try {

            if (token.type == FUNCTION) {

                opStack.push_back(token);

                printStacks();
            }



            else if (token.type == OPERATOR) {

                while (opStack.getSize() > 0 && opStack.back().value != "(" && (
                    opStack.back().precedence > token.precedence || (
                    opStack.back().precedence == token.precedence &&
                    token.associativity))) {

                        popAppend(temp, opStack, outStack);

                        printStacks();

                    }

                opStack.push_back(token);

                printStacks();

            }



            else if (token.type == LEFT_BRACKET) {

                opStack.push_back(token);

                printStacks();
            }

    

            else if (token.type == RIGHT_BRACKET) {

                while (opStack.getSize() > 0 && opStack.back().type != LEFT_BRACKET) {

                    popAppend(temp, opStack, outStack);

                    printStacks();

                }
                opStack.pop_back();

                printStacks();
            }



        } catch (...) {std::cout << "well shit, this isn't supposed to happen" << std::endl;}


    }



    while (opStack.getSize() > 0) popAppend(temp, opStack, outStack);

    
    std::cout << "equation in RPN: ";

    for (size_t i = 0; i < outStack.getSize(); ++i) std::cout << outStack[i].value << " ";

    std::cout << std::endl;

    return outStack;

}

std::vector<double> findNumbers(int type, Vector<double> hist) {

    if (type) return std::vector<double> {hist.operator[](hist.getSize() - 1), 0.0};

    else return std::vector<double> {hist.operator[](hist.getSize() - 2), hist.back()};

    return std::vector<double> {0.0, 0.0};
}

double shuntingYardEvaluator(Vector<Token> equation, bool isRadians) {

    Vector<Token> stack = equation;

    Vector<double> hist = {};

    while (stack.getSize() > 0 && stack.getSize() < 10000) {

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

            hist.push_back(i.math(i.apply, x, y, isRadians));

        }
    }

    return hist.operator[](0);

}



int main() {

    makeTokens();


    // bool isRadians = false

    // std::cout << "test: " << token.math(token.apply, 60, 0, isRadians) << std::endl;

    std::string equation = "4 + (3! * (52 + 73 * #(64) / 2 _ 220) _  2 ^ (5 _ 2)) / 15";

    // equation = "s(60)";



    Vector<Token> stack = shuntingYardConverter(equation);

    std::cout << "equation in RPN: ";
    for (size_t i = 0; i < stack.getSize(); ++i) {
        std::cout << "value: " << stack[i].value << std::endl << "type: " << stack[i].type << std::endl << std::endl;
    }
    std::cout << std::endl;


    // double solution = shuntingYardEvaluator(stack, isRadians);

    // std::cout << "solution: " << solution << std::endl;


}

