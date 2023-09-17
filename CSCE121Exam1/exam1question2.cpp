#include <iostream>
using namespace std;

int main() {
    
    int number;
    bool isNegative = false;
    cout << "Enter an integer which rating is to be determined: ";
    cin >> number;
    int originalNumber = number;
    if (number < 0) {
        number *= -1;
        isNegative = true;
    }

    int rating = 0;
    int location = 1;

    while (number > 0) {
        int digit = number % 10;
        if (digit % location == 0 && !isNegative) {
            rating += 1;
        } else if (digit % location != 0 && isNegative) {
            rating += 1;
        }
        number /= 10;
        location += 1;
    }

    if (originalNumber < 0)
        rating *= -1;

    cout << "\n" << endl;
    cout << "n = " << originalNumber << " has a rating of " << rating << endl;

    return 0;

}