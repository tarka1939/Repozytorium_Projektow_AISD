#pragma once
#define BLOCKSIZE 8
template <typename T>
struct Block {
	T body[BLOCKSIZE];
	int size = 0;
	bool AddValue(T value) {
		body[size] = value;
		size++;
		if (size == BLOCKSIZE)
			return false;
		return true;
	}
	bool RemoveValue(int index) {
		if (index == size - 1) {
			//delete[] body[index];
			size--;
			
		}
		else {
			//delete[] body[index];
			for (int i = index; i < size; i++) {
				body[i] = body[i + 1];
			}
			size--;
			
		}
		if (size == 0)
			return false;
		return true;
	}
};