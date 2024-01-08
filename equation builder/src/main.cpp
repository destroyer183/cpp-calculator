#include <iostream>
#include <deque>
#include <string>
#include <string.h>


const int TRIG_FUNCTION_SIN = 0;
const int TRIG_FUNCTION_COS = 1;
const int TRIG_FUNCTION_TAN = 2;

const bool L_BRACKET = true;
const bool R_BRACKET = false;



std::deque<std::string> list(std::string string) {
    std::deque<std::string> temp;
    for (char i : string) temp.push_back(std::string(1, i));
    return temp;
}

std::string join(std::deque<std::string> input, int start, int end) {

    std::deque<std::string> stack = {input.begin() + start, input.begin() + end};
    std::string temp = (std::string(stack.begin(), stack.end()));
    return temp;
}



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



    void trigType() { // when you see this, use a button on the breadboard to toggle this
        trigToggle = !trigToggle;
    }



    void unitType() { // when you see this, use a button on the breadboard to toggle this
        isRadians = !isRadians;
    }



    void updateText(int type = 0, std::deque<std::string> string = {}, std::deque<inline std::size_t> index = {}, int update = 0) {

        std::deque<char> chunk1;
        std::deque<char> chunk2;
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

        
    }





};




























int main()
{
    std::cout << "Hello world!" << std::endl;
}
