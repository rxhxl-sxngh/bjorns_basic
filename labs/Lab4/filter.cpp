#include <iostream>
#include <string>
#include<vector>
using std::cin, std::cout, std::endl, std::string;

int main() {
    string str;
    string filter;
    cout << "Please enter the sentence: ";
    cin >> str;
    cout << "Please enter the filter word: ";
    cin >> filter;
    string replacement;
    for (unsigned int i = 0; i < filter.size(); i++) {
        replacement.push_back('#');
    }
    size_t pos = str.find(filter);
    while (pos != string::npos) {
        str.replace(pos, filter.size(), replacement);
    }

    return 0;
}
