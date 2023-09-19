#include <iostream>
#include <string>
#include <limits>
#include "./string_calculator.h"

using std::cout, std::endl, std::cin;
using std::string;

int main() {
    cout << "String Calculator" << endl;
    cout << "\"q\" or \"quit\" or ctrl+d to exit" << endl;
    
    // TODO(student): implement the UI
    string lhs;
    string rhs;
    string operation; 

    do {
        cout << ">> ";
        cin >> lhs;
        if (lhs == "q" || lhs == "quit")
            break;
        cin >> operation;
        cin >> rhs;
        cout << "\n" << "ans =" << "\n" << endl;
        if(operation == "+")
            cout << "    " << add(lhs, rhs) << "\n" << endl;
        if(operation == "*")
            cout << "    " << multiply(lhs, rhs) << "\n" << endl;

    } while (lhs != "q" || lhs != "quit");

    cout << "\n" << "farvel!" << "\n" << endl;

}

