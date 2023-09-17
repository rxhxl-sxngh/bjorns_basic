#include <iostream>
using namespace std;

void decode(char alphabet[], unsigned int nums1[], unsigned int nums2[], unsigned int size) {
    //throw exception if the alphabet array has no characters to use for decoding
    if (alphabet[0] == '\0')
        throw std::invalid_argument("");

    //throw exception if size = 0
    if (size == 0)
        throw std::invalid_argument("");

    int index = 0;
    
    
    for (unsigned int i = 0; i < size; i++) {

        //alternate between nums1 and nums2
        if (i % 2 == 0) {
            index = nums1[i/2];
        } else {
            index = nums2[i/2];
        }


        //get correct value of alphabet
        int iterator = 0;
        int position = 0;
        while (iterator != index) {
            iterator += 1;
            position += 1;
            if (alphabet[position] == '\0')
                position = 0;
        }

        //output correct value of alphabet
        cout << alphabet[position];
    }

    //blank line for neatness
    cout << endl;

}


//check with main function
int main() {
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    unsigned int nums1[] = {38, 4, 26, 40, 4, 38};
    unsigned int nums2[] = {4, 19, 19, 13, 41};
    unsigned int size = 11;
    decode(alphabet, nums1, nums2, size);

    return 0;

}