// TODO: Implement this source file
#include <iostream>
#include <fstream>
#include <limits>
#include <stdexcept>
#include "MyString.h"


MyString::MyString() : size_(0), capacity_(1), string(new char[capacity_]) {
	string[0] = '\0';
}

MyString::MyString(const MyString &copy): size_(copy.size_), capacity_(copy.capacity_), string(new char[copy.capacity_]) {
	if(copy.capacity_ == 0) {
		capacity_ = 1;
		delete string;
		string = new char[1];
		string[0] = '\0';
	} else {
		for (size_t i = 0; i < size_; ++i) {
			this->string[i] = copy.at(i);
		}
	}
	
}

MyString::MyString(const char* s): size_(0), capacity_(1), string(new char[capacity_]) {
	string[0] = '\0';
    int size = 0;
    char letter = s[size];
    while (letter != '\0'){
        size++;
        letter = s[size];
    }
	capacity_ = size + 1;
	delete[] string;
	string = new char[capacity_];
	for(int i = 0; i < size; ++i){
        string[i] = s[i];
    }
    size_ = size;
    string[capacity_] = '\0';
}


MyString::~MyString() {
    delete[] string;
    size_ = 0;
    capacity_ = 0;
    string = nullptr;
}



void MyString::resize(size_t n) {
	char* copy = new char[n];
	for (unsigned int i = 0; i < size_ + 1; ++i) {
		copy[i] = string[i];
	}
	delete[] string;
	string = new char[n];
	string = copy;
	int size = 0;
    char letter = copy[size];
    while (letter != '\0'){
        size++;
        letter = copy[size];
    }
	size_ = size;
	capacity_ = n;
}

size_t MyString::capacity() const noexcept {
	return capacity_;
}

size_t MyString::size() const noexcept {
	return size_;
}

size_t MyString::length() const noexcept {
	return size_;
}

const char* MyString::data() const noexcept {
	return string;
}

bool MyString::empty() const noexcept {
	return size_ == 0;
}

const char& MyString::front() const {
	return string[0];
}

const char& MyString::at(size_t pos) const {
	if (pos >= size_) {
		throw std::out_of_range("that index does not exist");
	}
	return string[pos];
}

void MyString::clear() noexcept {
	delete[] string;
	string = new char[0];
	size_ = 0;
	capacity_ = 1;
}

		

MyString& MyString::operator= (const MyString& str) {
	if(this != &str) {
		if(str.capacity() == 0) {
			size_ = 0;
			capacity_ = 1;
			delete[] string;
			string = new char[capacity_];
			string[0] = '\0';

		} else {
			delete[] string;
			string = new char[str.capacity()];
			for (unsigned int i = 0; i < str.size(); ++ i) {
				string[i] = str.at(i);
			}
			size_ = str.size();
			capacity_ = str.capacity();
		}	
	}
	return *this;
}

MyString& MyString::operator+=(const MyString& str) {
	char* copy = new char[capacity_ + str.capacity()];
	size_t newCapacity = capacity_ + str.capacity();
	size_t newSize = size_ + str.size();
	for (unsigned int i = 0; i < size_; ++i) {
		copy[i] = string[i];
	}
	for (unsigned int i = 0; i < str.size(); ++i) {
		copy[i + size_] = str.at(i);
	} 
	delete[] string;
	string = new char[newCapacity];
	for(unsigned int i = 0; i < newSize; i++) {
		string[i] = copy[i];
	}
	capacity_ = newCapacity;
	size_ = newSize;
	return *this;
}

size_t MyString::find(const MyString& str, size_t pos) const noexcept {
	bool found = false;
	for(size_t i = pos; i < size_; i++) {
		if(string[i] == str.at(0)) {
			found = true;
			for(size_t j = 0; j < str.size(); j++) {
				if( i + j >= size_) {
					found = false;
					break;
				}
				if(string[i+j] != str.at(j)) {
					found = false;
					break;
				}
			}
			if(found) {
				return i;
			}
		}
	}
	return -1;
}

std::ostream& operator<< (std::ostream& os, const MyString& str){
    os << str.data();
    return os;
}