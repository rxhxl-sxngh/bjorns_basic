#include <iostream>

bool f(bool x, bool y, bool z) {
  // write your code to compute f(x,y,z) here
  bool value = false; // TODO: change this line
  if (x && y && z) {
    value = true;
  } else {
    value = x ^ (y || z);
  }
  return value;
}