#pragma once
#ifndef B_H
#define B_H
//#include "List.h"
#include <list>
//#include "Vector.h"
template <typename T>
class Queue
{
	private:
		std::list<T> data;
		int size=0;
	public:
		Queue();
		~Queue();
		void push(T value);
		T pop();
		T front();
		T back();
		bool isEmpty();
};
template <typename T>
Queue<T>::Queue()
{
}
template <typename T>
Queue<T>::~Queue()
{
	//data.~List();
	size = 0;
}
template <typename T>
void Queue<T>::push(T value)
{
	data.push_back(value);
	size++;
}
template <typename T>
T Queue<T>::pop()
{
	T out = data.front();
	data.pop_front();
	size--;
	return out;
}
template <typename T>
T Queue<T>::front()
{
	return data[size];
}

template <typename T>
T Queue<T>::back()
{
	return data[0];
}

template <typename T>
bool Queue<T>::isEmpty()
{
	return size == 0;
}
#endif // B_H