# include <iostream>
using namespace std;

struct backQueue {
    char* array = nullptr;
    int capacity = 0;
    int size = 0;
};
 
void push(backQueue& queue, char character) {
    // TODO: push()
    if(queue.array == nullptr) {
        queue.capacity = 1;
    }

    if(queue.size == queue.capacity || queue.capacity == 1) {

        queue.capacity *= 2;
        char* newArray = new char[queue.capacity];
        newArray[0] = character;
        for(int i = 0; i < queue.size; i++) {
            newArray[i+1] = queue.array[i];
        }
        queue.size += 1;
        queue.array = newArray;

    } else {

        char temp = queue.array[0];
        queue.array[0] = character;
        for(int i = 1; i < queue.size; i++) {
            char newTemp = queue.array[i];
            queue.array[i] = temp;
            temp = newTemp;
        }
        queue.array[queue.size] = temp;
        queue.size += 1;

    }

    
   
}
 
char pop(backQueue& queue) {
    // TODO: pop()
    if(queue.size == 0) {
        return '\0';
    } else {
        queue.size -= 1;
        return queue.array[queue.size];
    }
    
 
}
 
int main() {
    backQueue q;
 
    push(q, 'a');
    std::cout << pop(q) << '\n';
 
    // OPTIONAL TODO: add more test cases

    //additional test case
    backQueue test1;
    test1.array = new char[3]{'a','b','c'};
    test1.capacity = 4;
    test1.size = 3;
    push(test1, 'z');
    std::cout << pop(test1) << '\n';
    //output array after pop function has "resized" the array
    for(int i = 0; i < test1.size; i++) {
        cout << test1.array[i] << " ";
    }
    cout << '\n' << endl;

   
    delete[] q.array;
    delete[] test1.array;
}