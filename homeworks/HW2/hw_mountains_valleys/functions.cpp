#include <iostream>
#include "functions.h"
using namespace std;

using std::cout, std::endl;

bool is_valid_range(int a, int b) {
	// TODO(student): validate input range
	if (a >= 10 && a < 10000 && b >= 10 && b < 10000 && b >= a) {
		return true;
	} else {
		return false;
	}
}

char classify_mv_range_type(int number) {
	// TODO(student): return 'M' if number has /\/\... pattern,
	// return 'V' if number has \/\/ pattern, and return 'N' otherwise
	

	if (number < 100) {
		int laterDigit;
		int earlierDigit;
		laterDigit = number % 10;
		number /= 10;
		earlierDigit = number % 10; 
		if (laterDigit > earlierDigit) {
			return 'M';
		} else if (laterDigit < earlierDigit) {
			return 'V';
		} else {
			return 'N';
		}
	} else if (number >= 100 && number < 1000) {
		int firstDig;
		int secondDig;
		int thirdDig;
		thirdDig = number % 10;
		number /= 10;
		secondDig = number % 10;
		number /= 10;
		firstDig = number % 10;
		number /= 10;
		if (firstDig < secondDig && secondDig > thirdDig) {
			return 'M';
		} else if (firstDig > secondDig && secondDig < thirdDig) {
			return 'V';
		} else {
			return 'N';
		}
	} else if (number >= 1000 && number < 10000) {
		int firstDig;
		int secondDig;
		int thirdDig;
		int fourthDig;
		fourthDig = number % 10;
		number /= 10;
		thirdDig = number % 10;
		number /= 10;
		secondDig = number % 10;
		number /= 10;
		firstDig = number % 10;
		number /= 10;
		if (firstDig < secondDig && secondDig > thirdDig && thirdDig < fourthDig ) {
			return 'M';
		} else if (firstDig > secondDig && secondDig < thirdDig && thirdDig > fourthDig) {
			return 'V';
		} else {
			return 'N';
		}
	} else if (number >= 10000) {
		string recentType = "";
		string lastType;
		char numType = 'a';
		int laterDigit;
		int earlierDigit;
		while (number >= 10) {
			laterDigit = number % 10;
			number = number / 10;
			earlierDigit = number % 10;
			if (laterDigit < earlierDigit) {
				lastType = "V";
			} else if (earlierDigit < laterDigit) {
				lastType = "M";
			} else {
				numType = 'N';
				break;
			}
			if (lastType == recentType and numType != 'N'){
				numType = 'N';
				break;
			}
			recentType = lastType;
		}
		if (lastType == "M" and numType != 'N') {
			numType = 'M';
		} else if (lastType == "V" and numType != 'N') {
			numType = 'V';
		} 
		return numType;
	} else {
		return 'N';
	}


}

void count_valid_mv_numbers(int a, int b) {
	// TODO(student): count the number of valid mountain ranges and valley
	// ranges in the range [a, b] and print out to console using the format
	// in Requirement 4 of the homework prompt
	int mountainCount = 0;
	int valleyCount = 0;
	for (int x = a; x <= b; x++) {
		if (classify_mv_range_type(x) == 'M') {
			mountainCount += 1;
		} else if (classify_mv_range_type(x) == 'V') {
			valleyCount += 1;
		}
	}
	cout << "There are " << mountainCount << " mountain ranges and " << valleyCount << " valley ranges between " << a << " and " << b << "." << endl;
}