#include "Processor.h"
#include <stack>
#include <cmath>

Processor::Processor()
{
}

Processor* Processor::_processor = nullptr;

std::string Processor::ConvertToShuntingYard(std::string& s)
{
    std::string result = "", currentNumber = "";
    std::stack<unsigned char> operators;

    for (int i = 0; i < s.length(); i++) {
        if ((s[i] >= 48 && s[i] <= 57) || s[i] == '.') {
            currentNumber += s[i];
        }
        else {
            //Adds the current float to the result
            if (currentNumber.length() > 0) {
                result += currentNumber + " ";
                currentNumber = "";
            }
            
            //Seperates out negative numbers, tying the negative symbol to the number itself
            //If the char to the left of the '-' symbol is non-numeric treat it as a negate symbol
            if (s[i] == '-' && (i == 0 || (s[i - 1] < 48 || s[i - 1] > 57))) {
                //Adds the negative symbol to the result
                result += s[i];
                i++;

                //Adds the number to the result
                for (int j = i; j < s.length(); j++, i++) {
                    if ((s[i] >= 48 && s[i] <= 57) || s[i] == '.') {
                        result += s[i];
                    }
                    else {
                        break;
                    }
                }

                //Adds a space
                result += " ";
            }

            //Adds operators to the result if their priority is higher or equal to the current symbol being added to the stack
            while (!operators.empty() && priority[operators.top()] >= priority[s[i]]) {
                result += operators.top();
                result += " ";
                operators.pop();
            }

            //Adds the symbol to the stack
            operators.push(s[i]);
        }
    }

    //Ensures emplacement of any remaing numbers
    if (currentNumber.length() > 0) {
        result += currentNumber + " ";
        currentNumber = "";
    }

    //Ensures emplacement of any remaining operators
    while (!operators.empty()) {
        result += operators.top();
        result += " ";
        operators.pop();
    }

    //Return the trimmed result, no space at the end
    return result.substr(0,result.length()-1);
}

Processor* Processor::GetInstance()
{
    if (_processor == nullptr) {
        _processor = new Processor();
    }

    return _processor;
}

float Processor::Calculate(std::string s)
{
    if (s.length() == 0) {
        return 0.0f;
    }

    //Converts the inputed string to Reverse Polish Notation using the Shunting Yard Algorithm
    s = ConvertToShuntingYard(s);

    std::string currentNumber = "";
    std::stack<float> numbers;
    float result = 0.0;

    //Performs calculations based on the converted string
    for (int i = 0; i < s.length(); i++) {
        if ((s[i] >= 48 && s[i] <= 57) || s[i] == '.') {
            currentNumber += s[i];
        }
        else {
            //Adds the current number to the stack
            if (currentNumber.length() > 0) {
                numbers.push(std::stof(currentNumber));
                currentNumber = "";
            }

            //Ignoring spaces, preventing operations on too small of a stack
            if (s[i] != ' ' && (numbers.size() >= 2 || s[i] == '-')) {
                float temp = 0.0;

                //Performs operations based on the operator
                switch (s[i]) {
                case ADD: //Adds the two numbers at the top of the stack
                    temp = numbers.top();
                    numbers.pop();
                    temp += numbers.top();
                    numbers.pop();
                    numbers.push(temp);
                    break;
                case SUBTRACT://Subtracts the two numbers at the top of the stack, given its not a negate symbol
                    //Adds a negative number to the stack if '-' symbol is attached to a number
                    if (i + 1 < s.length() && (s[i + 1] >= 48 && s[i + 1] <= 57)) {
                        //Adds the negative symbol to the currentNumber variable
                        currentNumber += s[i];
                        i++;

                        //Gets the current negative float
                        for (int j = i; j < s.length(); j++, i++) {
                            if ((s[i] >= 48 && s[i] <= 57) || s[i] == '.') {
                                currentNumber += s[i];
                            }
                            else {
                                break;
                            }
                        }

                        //Adds the negative float to the stack
                        numbers.push(std::stof(currentNumber));
                        currentNumber = "";
                    }
                    //Otherwise treats the '-' symbol as a subtraction operator
                    else if(numbers.size() >= 2) {
                        temp = numbers.top();
                        numbers.pop();
                        temp = numbers.top() - temp;
                        numbers.pop();
                        numbers.push(temp);
                    }
                    break;
                case MULTIPLY://Multiplies two numbers at the top of the stack
                    temp = numbers.top();
                    numbers.pop();
                    temp *= numbers.top();
                    numbers.pop();
                    numbers.push(temp);
                    break;
                case DIVIDE://Divides two numbers at the top of the stack
                    temp = numbers.top();
                    numbers.pop();
                    if (temp == 0) {
                        return NAN;
                    }
                    temp = numbers.top() / temp;
                    numbers.pop();
                    numbers.push(temp);
                    break;
                case MOD://Modulus divides two numbers at the top of the stack
                    temp = numbers.top();
                    numbers.pop();
                    if (temp == 0) {
                        return NAN;
                    }
                    temp = std::fmod(numbers.top(), temp);
                    numbers.pop();
                    numbers.push(temp);
                    break;
                default:
                    break;
                }
            }
        }
    }

    //Adds any remaining numbers
    if (currentNumber.length() > 0) {
        numbers.push(std::stof(currentNumber));
    }

    //Returns the number at the top of the stack
    return numbers.top();
}

float Processor::SIN(float f) {
    return std::sinf(f);
}
float Processor::COS(float f) {
    return std::cosf(f);
}
float Processor::TAN(float f) {
    return std::tanf(f);
}