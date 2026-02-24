#pragma once

#include "List.h"
template <typename T>
class Stack
{
	private:
		List<T> data;
		int size=0;
	public:
	Stack();
	~Stack();
	void push(T value);
	T pop();
	T top();
	bool isEmpty();
	int getSize();
	T& operator[](int index);
};
template <typename T>

Stack<T>::Stack()
{

}
template <typename T>

Stack<T>::~Stack()
{

}
template <typename T>

void Stack<T>::push(T value)
{
	data.Append(value);
	size++;
}
template <typename T>

T Stack<T>::pop()
{
	size--;
	T n = data[size];
	data.Delete(size);
	
	return n;
}
template <typename T>

T Stack<T>::top()
{
	if (size == 0)
	{
		return 0;
	}
	return data[size-1];
}
template <typename T>

bool Stack<T>::isEmpty()
{
	return size == 0;
}
template <typename T>

int Stack<T>::getSize() {
	return size;
}
template <typename T>

T& Stack<T>::operator[](int index)
{
	return data[index];
}