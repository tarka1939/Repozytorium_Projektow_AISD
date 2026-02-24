#pragma once
#ifndef C_H
#define C_H
#include "Vector.h"
#include <String.h>
#include <iostream>
class myString
{
	private:
		Vector<char> data;
		int size=0;
	public:
		int getSize();
		myString();
		myString(char* str);
		~myString();
		bool isEmpty();
		void push(char c);
		void push(char* str);
		char pop();
		char top();
		void clear();
		myString& operator=(const char* str);
		myString& operator=(myString& str);
		int toInt();
		bool operator==(const char* str);
		bool operator==(myString& str);
		char& operator[](int index);
		
		friend std::istream& operator>> (std::istream& in, myString& str);
		friend std::ostream& operator<< (std::ostream& out, myString& str);

};

std::istream& operator>> (std::istream& in, myString& str);
std::ostream& operator<< (std::ostream& out, myString& str);
#endif // C_H