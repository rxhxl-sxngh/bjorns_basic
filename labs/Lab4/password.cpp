#include <iostream>
#include <string>
using std::cin, std::cout, std::endl, std::string;

int main() {
    string password;
    cout << "Please enter your text input: ";
    cin >> password;
    cout << "input: " << password << endl;
    string rep = "aeiou";
    string with = "@3!0^";
    string reverse;
    

    for (unsigned int i = 0; i < rep.size(); i++) {
        size_t position = 0;
        do {
            position = password.find_first_of(rep.at(i));
            if (position != string::npos) {
                password.at(position) = with.at(i);
        }
        } while (position != string::npos);
    }

    int length = password.size()-1;
    for (int i = length; i >= 0; i--)
        reverse += password[i];
    
    password += reverse;
    cout << "output: " << password;
    return 0;
}
