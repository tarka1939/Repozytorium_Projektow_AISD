#pragma once
template <typename T>
class Cell
{
	

	

public:
	T cell_value;
	Cell<T>* fpointer;
	Cell<T>* bpointer;
	Cell() {
		fpointer = nullptr;
		bpointer = nullptr;
	}
	Cell(T value) {
		cell_value = value;
		fpointer = nullptr;
		bpointer = nullptr;
	}
	Cell(T cell_value, Cell<T>* fpointer, Cell<T>* bpointer) {
		this->cell_value = cell_value;
		this->fpointer = fpointer;
		this->bpointer = bpointer;
	}

	
	T& GetValue() {
		return cell_value;
	};
	/*
	void SetValue(T value) {
		cell_value = value;
	};
	Cell<T>* GetBPointer() {
		return bpointer;
	};
	Cell<T>* GetFPointer() {
		return fpointer;
	};
	void SetFPointer(Cell<T>* ptr) {
		fpointer = ptr;
	};
	void SetBPointer(Cell<T>* ptr) {
		bpointer = ptr;
	};*/
	~Cell() {
		if (fpointer != nullptr)
			delete(fpointer);
	};
};

