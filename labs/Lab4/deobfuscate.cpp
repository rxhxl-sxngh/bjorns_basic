#include <iostream>
#include <string>
using std::cin; 
using std::cout; 
using std::endl; 
using std::string;

int main() {
    string str;
    string details;
    cout << "Please enter obfuscated sentence: ";
    cin >> str;
    cout << "Please enter deobfuscation details: ";
    cin >> details; 
    int pos = 0;
    for(unsigned int i = 0; i < details.size(); i++) {
        char c = details[i]; 
        pos += (c-48);
        str.insert(pos," ");    
        pos += 1; 
    }
    cout << "Deobfuscated sentence: " << str;

    return 0;
}
