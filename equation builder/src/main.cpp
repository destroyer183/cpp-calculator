#include <iostream>
#include <deque>
#include <bits/stdc++.h>
#include <string>
#include <string.h>
#include <map>
#include <C:\Users\aob\Documents\Coding Stuff\my stuff\c and c++ stuff\c++ stuff\calculator stuff\parser\src\main.cpp>
#include <math.h>



enum TrigFunction {
    TRIG_FUNCTION_SIN,
    TRIG_FUNCTION_COS,
    TRIG_FUNCTION_TAN,
};

enum Bracket {
    R_BRACKET,
    L_BRACKET
};



std::deque<std::string> list(std::string string) {
    std::deque<std::string> temp;
    for (char i : string) temp.push_back(std::string(1, i));
    return temp;
}



std::string join(std::deque<std::string> input, int start = 0, int end = -1) {

    std::string temp;

    if (end == -1) end = input.size();

    std::deque<std::string> stack(input.cbegin() + start, input.cbegin() + end);

    for (std::string str : stack) {
        temp += str;
    }

    return temp;
}


double roundNumber(double number, int precision) { // function to round a double to a variable number of decimal places

    double multiplier = pow(10, precision); // create variable to represent how many decimal places need to be maintained

    number *= multiplier; // multiply input number by the multiplier to move all necessary decimal numbers to the left of the decimal point

    number = round(number); // round number to the nearest integer

    number /= multiplier; // divide number by the multiplier to return all maintained decimal numbers to the right of the decimal point

    return number; // return output number
}

/*

std::string normal  = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+-=().";
std::string super_s = "ᴬᴮᶜᴰᴱᶠᴳᴴᴵᴶᴷᴸᴹᴺᴼᴾQᴿˢᵀᵁⱽᵂˣʸᶻᵃᵇᶜᵈᵉᶠᵍʰᶦʲᵏˡᵐⁿᵒᵖ۹ʳˢᵗᵘᵛʷˣʸᶻ⁰¹²³⁴⁵⁶⁷⁸⁹⁺⁻⁼⁽⁾‧";
std::map<char, char> superscriptTable;

std::string maketrans(std::string input) {

    std::string output;

    for (char i : input) {
        output += std::string(1, superscriptTable[i]);
    }

    return output;
}
*/





class Logic {

    public:

    std::deque<std::string> equation;
    int bracketNum;
    bool exponent;
    std::string output;
    std::deque<std::string> memory;

    Logic (std::deque<std::string> equationInput = {""}, int bracketNumInput = 0, bool exponentInput = false, std::string outputInput = "", std::deque<std::string> memoryInput = {}) {

        equation = equationInput;
        bracketNum = bracketNumInput;
        exponent = exponentInput;
        output = outputInput;
        memory = memoryInput;
    }
};



// main class to handle all the gui stuff
class Gui {

    public:

    bool trigToggle;
    bool isRadians;
    std::deque<std::string> equationText;
    std::deque<std::string> displayText;
    Logic logic;

    Gui (bool trigToggleInput = false, bool isRadiansInput = false, std::deque<std::string> equationTextInput = {""}, std::deque<std::string> displayTextInput = {"", ""}) {

        trigToggle = trigToggleInput;
        isRadians = isRadiansInput;
        equationText = equationTextInput;
        displayText = displayTextInput;
    }

    void createGui() {}



    void trigType() { // when you see this, use a button on the breadboard to toggle this
        trigToggle = !trigToggle;
    }



    void unitType() { // when you see this, use a button on the breadboard to toggle this
        isRadians = !isRadians;
    }


    
    void updateText(int type = 0, std::deque<std::string> string = {}, std::deque<size_t> index = {}, int update = 0) {

        std::string temp;

        if (string.empty()) {
            string = {"", "", ""};
        }

        int d = 0;

        if (index.empty()) {
            index = {logic.equation.size(), equationText.size(), displayText.size()};

            d = logic.bracketNum;
        }

        // simplify variables
        std::deque<std::string> a = logic.equation;
        std::deque<std::string> b = equationText;
        std::deque<std::string> c = displayText;
        bool e = logic.exponent;

        logic.equation = list(join(a, 0, index[0] - d) + string[0] + join(a, index[0] - d, a.size() - 1));

        // this if statement should superscript 'string[1]'
        if (e) equationText = list(join(b, 0, index[1] - d) + string[1] + join(b, index[1] - d, b.size() - 1));
        
        else   equationText = list(join(b, 0, index[1] - d) + string[1] + join(b, index[1] - d, b.size() - 1));
        
        if (!type) {

            displayText = list(string[2]);

            displayText.push_back("");
        }

        else {

            displayText = list(join(c, 0, index[2]) + string[2] + join(c, index[2], c.size() - 1));
        }



        // update display
        if (!update) {

        } else if (update) {

        } else if (update == 2) {

        }
    }



    // function bound to the clear button that clears the variables and display.
    void clear(bool type = true) {

        if (type) {

            // reset variables
            logic.equation = {""};

            equationText = {""};

            displayText = {"", ""};

            logic.bracketNum = 0;

            logic.exponent = false;



            // update display

        } else {

            std::deque<std::string> characters{"1", "2", "3", "4", "5", "6", "7", "8", "9", "0", ".", "-"};

            // check if there is anything in the display text variable
            if (find(characters.begin(), characters.end(), equationText.back()) != characters.end()) {

                // delete the last digit in each variable
                logic.equation.pop_back();

                equationText.pop_back();

                // only delete from the display text if there is stuff to delete
                if (displayText.size()) displayText.pop_back();

                updateText(2);
            }



            // check if there is an operator in the right-most position in the equation
            else if (equationText.back() == " ") {

                // delete the last operator
                logic.equation = {logic.equation.cbegin(), logic.equation.cend() - 3};

                equationText = {equationText.cbegin(), equationText.cend() - 3};

                // update display
                updateText(2);
            }
        }

        // check if the last thing entered in was an operator
        // check if the last thing is a bracket, if it is, go inside the bracket instead of deleting it
            // figure out how to show this
    }



    // the function bound to the 'equals' button to output a result for an equation.
    void calculate() {

        std::string answer;

        std::cout << "equation: " << join(logic.equation) << std::endl;

        // assemble equation list into a string
        std::string equationStr = join(logic.equation);

        // this is necessary
        if (equationStr == "9 + 10") answer = "21";

        else answer = shuntingYardEvaluator(equationStr, isRadians);

        if (!answer.size()) {

            std::cout << "Could not calculate answer." << std::endl;

            return;
        }

        std::cout << "output: " << answer << std::endl;

        // round the output to the specified number of decimal places
        logic.output = std::to_string(roundNumber(std::stod(answer), 5)); // put round number variable here once gui is made



        // edit display strings
        equationText.push_back(" = " + logic.output);

        displayText = {logic.output};

        logic.bracketNum = 0;



        // update display
        updateText(2);



        // reset variables
        equationText = {logic.output};

        logic.equation = {logic.output};
    }



    // the function bound to the addition button to tell the calculate function which mathematical operation to perform when it is pressed.
    void handleOperator(std::string operation) {

        try {

            std::string text = "sctSCTlf^#/*%+_";

            if (find(list(text).begin(), list(text).end(), equationText[-2 - logic.bracketNum]) == list(text).end()) {

                if (operation == " _ ") {

                    updateText(0, {operation, " - ", ""}, {}, 1);
                }



                else {

                    // add operator to equation and display strings
                    updateText(0, {operation, operation, ""}, {}, 1);
                }
            }

        } catch(...) { // ask ryan which format looks better

            if (operation == " _ ") {

                updateText(0, {operation, " - ", ""}, {}, 1);
            }



            else {

                // add operator to equation and display strings
                updateText(0, {operation, operation, ""}, {}, 1);
            }
        }
    }



    // function bound to the decial button to allow decimal numbers to be inputted.
    void putDecimal() {

        std::deque<std::string> empty{""};

        if (displayText == empty) {

            // put the decimal in the equation and display strings
            updateText(1, {"0.", "0.", "0."});
        }



        else if (find(displayText.begin(), displayText.end(), ".") == displayText.end()) {

            // put the decimal in the equation and display strings
            updateText(1, {".", ".", "."});
        }
    }



    // function bound to the integer button to allow the user to toggle a number between positive and negative.
    void negative() {

        try {

            std::deque<std::string> empty{""};

            // check to see if there is anything in the display text
            if (displayText == empty) {

                // add the integer sign to the number if there is nothing else in the equation
                updateText(0, {"-", "-", "-"});

                return;
            }



            // find where display text is within the equation text
            inline auto temp = find(equationText.begin(), equationText.end(), join(displayText));

            size_t index;

            if (temp != equationText.end()) {
                index = temp - equationText.begin();
            } 



            if (find(displayText.begin(), displayText.end(), "-") == displayText.end()) {

                if (equationText[index] != "-") {

                    // put an integer sign on the number if it doesn't have one
                    updateText(1, {"-", "-", "-"}, {index, index, 0});
                }

            } else {

                // remove the integer sign from the number
                logic.equation.erase(logic.equation.begin() + index);

                equationText.erase(equationText.begin() + index);

                displayText.erase(displayText.begin() + index);



                // update display
                updateText(2);
            }

        } catch(...) {

            // add the integer sign to the number if there is nothing else in the equation
            updateText(1, {"-", "-", "-"});
        }
    }



    // function to input numbers.
    void putNumber(int x) {

        // allow for bracket multiplication without pressing the multiplication button
        if (logic.equation[-1 - logic.bracketNum] == ")") {

            for (std::string i : list(" * ")) logic.equation.insert((logic.equation.end() - logic.bracketNum), i);
        }

        // put the number in the equation and display strings
        updateText(1, {std::to_string(x), std::to_string(x), std::to_string(x)});
    }



    // function bound to the exponent button that allows for exponents to be used.
    void putExponential(int ctrlExp = -1) {}
    





};




























int main()
{
    

    std::string input = "Hello World!";

    /*
    for (size_t i = 0; i < normal.size(); i++) {
        superscriptTable[normal[i]] = super_s[i];
    }

    std::cout << "superscript table: " << std::endl;
    std::cout << "normal: ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+-=()." << std::endl;
    std::cout << "super_s: ᴬᴮᶜᴰᴱᶠᴳᴴᴵᴶᴷᴸᴹᴺᴼᴾQᴿˢᵀᵁⱽᵂˣʸᶻᵃᵇᶜᵈᵉᶠᵍʰᶦʲᵏˡᵐⁿᵒᵖ۹ʳˢᵗᵘᵛʷˣʸᶻ⁰¹²³⁴⁵⁶⁷⁸⁹⁺⁻⁼⁽⁾‧" << std::endl << std::endl; // don't print superscripted characters
    std::cout << "original string: " << input << std::endl;
    std::cout << "superscripted string: " << maketrans(input) << std::endl;
    */

   std::deque<std::string> test = {"Hel", "lo", " Wo", "rl", "d!"};

   std::cout << "original deque: ";
   for (std::string str : test) {std::cout << "\"" << str << "\", ";}

   std::cout << std::endl;

   std::string output = join(test);

   std::cout << "joined deque: " << output;


}
