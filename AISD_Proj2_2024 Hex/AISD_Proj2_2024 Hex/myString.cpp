#include "myString.h"

int myString::getSize()
{
	return size;
}

myString::myString()
{

}

myString::myString(char* str)
{
	for (int i = 0; i < strlen(str); i++)
	{
		data.push(str[i]);
	}
	size = strlen(str);
}

myString::~myString()
{

}

bool myString::isEmpty()
{
	return false;
}

void myString::push(char c)
{
	data.push(c);
	size++;
}
void myString::push(char* str)
{
	for (int i = 0; i < strlen(str); i++)
	{
		data.push(str[i]);
	}
	size += strlen(str);
}
char myString::pop()
{
	size--;
	return data.pop();
}

char myString::top()
{
	return data[size-1];
}

void myString::clear()
{
	data.clear();
	size = 0;
}

myString& myString::operator=(const char* str)
{
	data.clear();
	for (int i = 0; i < strlen(str); i++)
	{
		data.push(str[i]);
	}
	size = strlen(str);
	return *this;
}

myString& myString::operator=(myString& str)
{
	data.clear();
	for (int i = 0; i < str.size; i++)
	{
		data.push(str[i]);
	}
	size = str.size;
	return *this;
}

int myString::toInt()
{
	int result = 0;
	bool isNegative = false;
	if (data[0] == '-') {
		isNegative = true;
	}
	if (isNegative)
	{
		for (int i = 1; i < data.getSize(); i++)
		{
			result = result * 10 + (data[i] - '0');
		}
		result = -result;
	}
	else
		for (int i = 0; i < data.getSize(); i++)
		{
			result = result * 10 + (data[i] - '0');
		}
	return result;
}

bool myString::operator==(const char* str)
{
	if (data.getSize() != strlen(str))
	{
		return false;
	}
	for (int i = 0; i < data.getSize(); i++)
	{
		if (data[i] != str[i])
		{
			return false;
		}
	}
	return true;
}

bool myString::operator==(myString& str)
{
	if (size != str.size)
	{
		return false;
	}
	for (int i = 0; i < data.getSize(); i++)
	{
		if (data[i] != str.data[i])
		{
			return false;
		}
	}
	return true;
}



char& myString::operator[](int index)
{
	return data[index];
}

std::istream& operator>>(std::istream& in, myString& str)
{
	char* temp = new char[1000];
	in >> temp;
	str = temp;
	return in;
}

std::ostream& operator<<(std::ostream& out, myString& str)
{
	for (int i = 0; i < str.getSize(); i++)
	{
		out << str[i];
	}
	return out;
}