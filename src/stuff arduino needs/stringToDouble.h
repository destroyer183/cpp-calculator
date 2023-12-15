
#ifndef STRINGTODOUBLE_H
#define STRINGTODOUBLE_H


double mapping(char input) { // wish I could use actual mapping for this, but arduino doesn't have it

    switch (input) {
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        case '0': return 0;
        default: return -1;
        
    }
}

double pow(double base, double power) {

    double output = base;

    for (int i = 0; i < power-1; i++) output *= base;

    return output;
}


double stringToDouble(String input) {

    double output = 0;
    
    bool negative = false;
    bool decimal = false;
    int decimalIndex = 0;

    for (char i : input) {

        double num = mapping(i);

        if (decimal) decimalIndex++;

        if (i == '-') {negative = true; continue;}
        if (i == '.') {decimal = true; continue;}


        else if (num == 0) {
            if (!decimal) output *= 10;
        }        

        else {

            if (decimal) output += num / (pow(10, decimalIndex));

            else output = output * 10 + num;
        }

    }

    if (negative) output *= -1;

    return output;
}

#endif