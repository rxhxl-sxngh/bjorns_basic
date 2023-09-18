#include <iostream>
#include <string>
#include "./string_calculator.h"

using std::cout, std::endl;
using std::string;

unsigned int digit_to_decimal(char digit) {
    // TODO(student): implement
    if (digit < 48 || digit > 57)
        throw std::invalid_argument("");
    return digit - 48;
}

char decimal_to_digit(unsigned int decimal) {
    // TODO(student): implement
    if (decimal > 9)
        throw std::invalid_argument("");
    return  char(decimal + 48);
}

string trim_leading_zeros(string num) {
    // TODO(student): implement
    bool isNegative = false;

    if (num.at(0) == '-') {
        isNegative = true;
        num.erase(0,1);
    }

    while(num.at(0) == '0') {
        if(num.size() == 1)
            break;
        num.erase(0,1);
    }

    if (isNegative && num != "0")
        return '-' + num;

    return num;
}

string add(string lhs, string rhs) {
    // TODO(student): implement
    string answer = "";
    int decimal;
    lhs = trim_leading_zeros(lhs);
    rhs = trim_leading_zeros(rhs);
    bool isNegative = false;

    if (lhs.at(0) == '-') {
        isNegative = true;
        lhs.erase(0,1);
        rhs.erase(0,1);
    }

    bool leftover = false;
    if (lhs.size() == rhs.size()) {
        for (int i = lhs.size()-1; i >= 0; i--) {
            decimal = digit_to_decimal(lhs.at(i)) + digit_to_decimal(rhs.at(i));
            if(leftover) {
                decimal += 1;
                leftover = false;
            }
            if (decimal >= 10) {
                leftover = true;
                answer = decimal_to_digit(decimal - 10) + answer;
            } else {
                answer = decimal_to_digit(decimal) + answer;
            }
        }
        if(leftover)
            answer = "1" + answer;
    }

    if (lhs.size() < rhs.size()) {
        string rhsExtra = rhs.substr(0, (rhs.size() - lhs.size()));
        string rhsNotExtra = rhs.substr(rhsExtra.size());
        for (int i = lhs.size()-1; i >= 0; i--) {
            decimal = digit_to_decimal(lhs.at(i)) + digit_to_decimal(rhsNotExtra.at(i));
            if(leftover) {
                decimal += 1;
                leftover = false;
            }
            if (decimal >= 10) {
                leftover = true;
                answer = decimal_to_digit(decimal - 10) + answer;
            } else {
                answer = decimal_to_digit(decimal) + answer;
            }
        }
        while(leftover) {
            for (int i = rhsExtra.size()-1; i >= 0; i--) {
                decimal = digit_to_decimal(rhsExtra.at(i)) + 1;
                if (decimal == 10) {
                    leftover = true;
                    rhsExtra.at(i) = '0';
                } else {
                    rhsExtra.at(i) = decimal_to_digit(decimal);
                    leftover = false;
                    break;
                }
            }
            if(leftover) {
                rhsExtra = "1" + rhsExtra;
                leftover = false;
            }
        }
        answer = rhsExtra + answer;
    }

    if (rhs.size() < lhs.size()) {
        string lhsExtra = lhs.substr(0, (lhs.size() - rhs.size()));
        string lhsNotExtra = lhs.substr(lhsExtra.size());
        for (int i = rhs.size()-1; i >= 0; i--) {
            decimal = digit_to_decimal(rhs.at(i)) + digit_to_decimal(lhsNotExtra.at(i));
            if(leftover) {
                decimal += 1;
                leftover = false;
            }
            if (decimal >= 10) {
                leftover = true;
                answer = decimal_to_digit(decimal - 10) + answer;
            } else {
                answer = decimal_to_digit(decimal) + answer;
            }
        }
        while(leftover) {
            for (int i = lhsExtra.size()-1; i >= 0; i--) {
                decimal = digit_to_decimal(lhsExtra.at(i)) + 1;
                if (decimal == 10) {
                    leftover = true;
                    lhsExtra.at(i) = '0';
                } else {
                    lhsExtra.at(i) = decimal_to_digit(decimal);
                    leftover = false;
                    break;
                }
            }
            if(leftover) {
                lhsExtra = "1" + lhsExtra;
                leftover = false;
            }
        }
        answer = lhsExtra + answer;
    }

    if (isNegative && answer != "0")
        answer = "-" + answer;

    return answer;
}

string multiply(string lhs, string rhs) {
    // TODO(student): implement
    string answer = "0";
    string temp = "";
    int decimal;
    lhs = trim_leading_zeros(lhs);
    rhs = trim_leading_zeros(rhs);
    int leftover = 0;

    bool lhsNegative = false;
    bool rhsNegative = false;
    if (lhs.at(0) == '-') {
        lhsNegative = true;
        lhs.erase(0,1);
    }
    if (rhs.at(0) == '-') {
        rhsNegative = true;
        rhs.erase(0,1);
    }

    
    for (int i = lhs.size()-1; i >= 0; i--) {
        for (int x = rhs.size()-1; x >= 0; x--) {
            decimal = digit_to_decimal(lhs.at(i)) * digit_to_decimal(rhs.at(x)) + leftover;
            if (decimal >= 10) {
                temp = decimal_to_digit(decimal % 10) + temp;
                leftover = decimal / 10;
            } else {
                temp = decimal_to_digit(decimal) + temp;
                leftover = 0;
            }
        }
        temp = decimal_to_digit(leftover) + temp;
        for(int j = ((lhs.size()-1)-i); j > 0; j--)
            temp += "0";
        
        answer = add(answer, temp);
        temp = "";
        leftover = 0;
    }


    if (lhsNegative ^ rhsNegative && answer != "0")
        answer = "-" + answer;
    return answer;
}
