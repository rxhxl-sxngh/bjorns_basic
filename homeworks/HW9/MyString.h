// TODO: Implement this header file
#ifndef MYSTRING_H
#define MYSTRING_H
#include <iostream>

class MyString {
	private:
		size_t size_;
		size_t capacity_;
		char* string;
	public:
		MyString();

		~MyString();

		MyString(const char* s);

		MyString(const MyString &copy);

		void resize(size_t n);

		size_t capacity() const noexcept;

		size_t size() const noexcept;

		size_t length() const noexcept;

		const char* data() const noexcept;

		bool empty() const noexcept;

		const char& front() const;

		const char& at(size_t pos) const;

		void clear() noexcept;

		

		MyString& operator= (const MyString& str);

		MyString& operator+= (const MyString& str);

		size_t find(const MyString& str, size_t pos = 0) const noexcept;



};

std::ostream& operator<< (std::ostream& os, const MyString& str);

#endif