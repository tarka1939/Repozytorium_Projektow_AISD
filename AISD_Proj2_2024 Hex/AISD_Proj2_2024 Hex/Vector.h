#pragma once
#ifndef A_H
#define A_H

#include <math.h>

template <typename T>
class Vector
{
	private: 
		T* data;
		int size;
		int capacity;
	public:
		void clear();
		Vector();
		~Vector();
		void push(T value);
		void resize();
		T pop();
		T front();
		T back();
		T& operator[](int index);
		bool isEmpty();
		int getSize();

};



template <typename T>
Vector<T>::Vector()
{
	capacity = 10;
	size = 0;
	data = new T[capacity];
}
template <typename T>
Vector<T>::~Vector()
{
}

template <typename T>
void Vector<T>::push(T value)
{
	if (size == capacity)
	{
		resize();
	}
	data[size] = value;
	size++;
}

template <typename T>
void Vector<T>::resize()
{
	capacity = ceil(capacity * (1 + log10(2)));
	T* temp = new T[capacity];
	for (int i = 0; i < size; i++)
		temp[i] = data[i];
	delete[] data;
	data = temp;
}

template <typename T>
T Vector<T>::pop()
{
	return data[--size];
}

template <typename T>
T Vector<T>::front()
{
	if (size == 0)
		return -1;
	return data[size - 1];
}

template <typename T>
T Vector<T>::back()
{
	if (size == 0)
		return -1;
	return data[0];
}

template<typename T>
inline T& Vector<T>::operator[](int index)
{
	return data[index];
}

template <typename T>
bool Vector<T>::isEmpty()
{
	return size == 0;
}

template <typename T>
int Vector<T>::getSize()
{
	return size;
}

template <typename T>
void Vector<T>::clear()
{
	size = 0;

}
//begin function
template <typename T>
T* begin(Vector<T>& v)
{
	return &v[0];
}
//end function
template <typename T>
T* end(Vector<T>& v)
{
	return &v[v.getSize()];
}

#endif // A_H