#pragma once
#include "Cell.h"
template <typename T>
class List
{
	bool CheckShorter(int size, int index) {
		return (size / 2 <= index); //Prawda jeœli index jest w czêœci listy bli¿ej ogona
	}
	Cell<T>* head = new Cell<T>;
	Cell<T>* tail = head;
	
	Cell<T>* GetOnIndex(int index) {
		if (index == 0 || index == -size)
			return head;
		else if (index == -1 || index == size - 1)
			return tail;
		else if (index == size) {
			Cell<T>* next = new Cell<T>();
			next->bpointer=tail;
			tail->fpointer=next;
			tail = next;
			size++;
			return next;
		}
		else {
			if (index < 0)
				index = index + size;
			if (CheckShorter(size, index)) {
				return IFB(size - index - 1);
			}
			else {
				return IFF(index);

			}
		}
	}

	Cell<T>* IFF(int index) {
		Cell<T>* current = head;
		for (int i = 0; i < index; i++) {
			current = current->fpointer;
		}
		return current;
	}

	Cell<T>* IFB(int index) {
		Cell<T>* current = tail;
		for (int i = 0; i < index; i++) {
			current = current->bpointer;
		}
		return current;
	}
public:
	int size = 1;
	List() {
	}


	/*List(std::initializer_list<T> list)
		: size{ int(list.size()) } {
		Cell<T>* first = new Cell<T>();
		for (T var : list) {

			Append(var);

		}
		Cell<T>* tmp = first->GetFPointer();
		tmp->SetBPointer(nullptr);
		delete(first);
		first = tmp;
	}*/
	void Append(T val) {

		Cell<T>* next = new Cell<T>(val);

		size++;
		if (size == 0) {
			tail = next;
			head = next;
			size++;
		}
		else {
			next->bpointer = tail;
			tail->fpointer = next;
			tail = next;
		}
	}/*
	void Prepend(T val) {
		Cell<T>* back = new Cell<T>(val);
		size++;
		if (size == 1) {
			head = back;
			tail = back;
		}
		else {
			back->SetFPointer(head);
			head->SetBPointer(back);
			head = back;
		}
	}
	void InsertP(T val, int index) {
		Cell<T>* current = GetOnIndex(index);
		size++;

		if (size == 1) {
			Cell<T>* next = new Cell<T>(val);
			head = next;
			tail = next;
		}
		else {
			if (current == head) {

				Cell<T>* next = new Cell<T>(val, current, nullptr);
				current->SetBPointer(next);
				head = next;
			}
			else {
				Cell<T>* next = new Cell<T>(val, current, current->GetBPointer());
				current->GetBPointer()->SetFPointer(next);
				current->SetBPointer(next);
			}
		}

	}
	void InsertA(T val, int index) {
		Cell<T>* current = GetOnIndex(index);
		size++;
		//std::cout<<"index: " << index<<std::endl;

		if (size == 1) {
			Cell<T>* next = new Cell<T>(val);
			head = next;
			tail = next;
		}
		else {
			//std::cout << "current: " << current->GetValue()<<std::endl;
			//std::cout << "InsertA: " << current->GetValue();
			if (current == tail) {

				Cell<T>* next = new Cell<T>(val, nullptr, current);

				current->SetFPointer(next);
				tail = next;
			}
			else {
				Cell<T>* next = new Cell<T>(val, current->GetFPointer(), current);
				current->GetFPointer()->SetBPointer(next);
				current->SetFPointer(next);

			}
		}

	}*/
	void Delete(int index) {
		Cell<T>* to_delete = GetOnIndex(index);
		Cell<T>* back = to_delete->bpointer;
		Cell<T>* next = to_delete->fpointer;
		if (size == 1) {
			head = new Cell<T>;
			tail = head;
			return;
		}
		else {
			if (to_delete == head) {
				head = next;
				next->bpointer=back;
			}
			else if (to_delete == tail) {
				tail = back;
				back->fpointer=next;
			}
			else {
				next->bpointer=back;
				back->fpointer=next;
			}
			to_delete->bpointer=nullptr;
			to_delete->fpointer=nullptr;
			delete(to_delete);
		}
		if (size != 0)
			size--;
	}
	
	/*Cell<T>* GetHPointer() {
		return head;
	};
	Cell<T>* GetTPointer() {
		return tail;
	};*/
	int GetSize() {
		return size;
	};
	 T& operator[](int index) {
		Cell<T>* cell = GetOnIndex(index);
		return cell->GetValue();
	}
};



