
#include <iostream>
#include "functions.h"
using std::cout;


int Largest(int a, int b, int c) {
  int values[3] = {a, b, c};
  int large = a;
  for (int i = 0; i < 3; i++) {
    if (values[i] > large) {
      large = values[i];
    }
  }
  return large;
}

bool SumIsEven(int a, int b) {
  if(((a+b)%2) == 0){
    return true;
  } else {
    return false;
  }
}

int BoxesNeeded(int apples) {
  if(apples <= 0) {
    return 0;
  } else if (apples % 20 == 0) {
    return apples/20;
  }
  return 1+(apples/20);
}

bool SmarterSection(int A_correct, int A_total, int B_correct, int B_total) {
  if (A_correct > A_total || B_correct > B_total || A_correct < 0 || A_total < 0 || B_correct < 0 || B_total < 0) {
    throw std::invalid_argument("");
  }
  double A_corr = A_correct;
  double A_tot = A_total;
  double B_corr = B_correct;
  double B_tot = B_total;
  return (A_corr/A_tot) > (B_corr/B_tot);
}


bool GoodDinner(int pizzas, bool is_weekend) {
  if (is_weekend) {
    return pizzas >= 10;
  }
  if (pizzas >= 10 && pizzas <= 20) {
    return true;
  } 
  return false;
}

int SumBetween(int low, int high) {
  
  
  if (low > high)
    throw std::invalid_argument("");

  if (low < 0 && high > 0 && abs(high) == abs(low)) {
    return 0;
  } else if (low == -2147483648 && high == 2147483647) {
    return low;
  }

  int value = 0;
  if (low < 0 && high > 0 && abs(high) > abs(low)) {

    for(int i = abs(low)+1; i <= high; i++) {
      if(i < 0)
        break;
      if((INT32_MAX - value) < i) {
        throw std::overflow_error("");
      }
      value += i; 
    }
      
  } else if (low < 0 && high > 0 && abs(low) > abs(high)) {

    for (int i = (high*-1)-1; i >= low; i--) {
      if(i > 0)
        break;
      if((INT32_MIN - value) > i) {
        throw std::overflow_error("");
      }
      value += i;
    }
      
  } else if (low >= 0 && high >= 0){

    for (int i = low; i <= high; i++) {
      if(i < 0)
        break;
      if((INT32_MAX - value) < i) {
        throw std::overflow_error("");
      }
      value += i;
    }

  } else if (low <= 0 && high <= 0) {

    for (int i = high; i >= low; i--) {
      if(i > 0)
        break;
      if((INT32_MIN - value) > i) {
        throw std::overflow_error("");
      }
      value += i;

    }
  }
  return value;
}

int Product(int a, int b) {
  if (a > 0) {

    if (b > 0) {
      if ((INT32_MAX/a) < b) {
        throw std::overflow_error("");
      }
    } 
    else if (b < 0) {
      if ((INT32_MIN/b) < a) {
        throw std::overflow_error("");
      }
    }

  } 
  else if (a < 0) 
  {
    if (b > 0) {
      if((INT32_MIN/a) < b) {
        throw std::overflow_error("");
      }
    } else if (b < 0) {
      if((INT32_MAX/a) > b) {
        throw std::overflow_error("");
      }
    }
    
  }

  return a * b;
}