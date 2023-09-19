#include <iostream>
using std::cout;
using std::endl;
using std::string;

int howdy(int &a, int b);
int gigEm(int c, int& d);

struct thing {
   string label;
   int howMany;
   thing() : label(""), howMany(0) {}
};

int main() {
   int s = 5;
   int t = 4;
   
   int y = gigEm(s, t);
   
   int z = howdy(y, s);

   thing* some = new thing();
   thing* many = new thing();

   some->label = "Shoe";
   some->howMany = y;
   many->label = "Toy";
   many->howMany = z;

   cout << "Items from the " << s << "&" << t << " store" << endl;
   cout << (*some).label << "'s quantity: " <<
      (*some).howMany << endl;
   cout << (*many).label << "'s quantity: " <<
      (*many).howMany << endl;

  delete some;
  many = nullptr;
}

int howdy(int &a, int b) {
   a /= 4;
   b *= 3;
   int temp = a + b + 9;
   return temp;
}

int gigEm(int c, int& d) {
   d = 10;
   int temp = howdy(c, d);
   temp += c;
   return temp;
}