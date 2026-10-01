#pragma once
//binary min-heap of (cost, id) pairs used as the priority queue in Dijkstra's algorithm
//entries are compared by cost, then by id, so nodes with equal cost come out lowest id first
//outdated entries are left in the heap and skipped by the caller (no decrease-key needed)
struct HeapEntry {
	int cost;
	int id;
};

class MinHeap
{
public:
	MinHeap(int initialCapacity = 16) {
		capacity = initialCapacity > 0 ? initialCapacity : 16;
		size = 0;
		data = new HeapEntry[capacity];
	}
	~MinHeap() {
		delete[] data;
	}
	MinHeap(const MinHeap&) = delete;
	MinHeap& operator=(const MinHeap&) = delete;

	bool isEmpty() {
		return size == 0;
	}
	void push(int cost, int id) {
		if (size == capacity)
			grow();
		HeapEntry entry = { cost, id };
		//sift up
		int i = size++;
		while (i > 0) {
			int parent = (i - 1) / 2;
			if (!less(entry, data[parent]))
				break;
			data[i] = data[parent];
			i = parent;
		}
		data[i] = entry;
	}
	HeapEntry pop() {
		HeapEntry top = data[0];
		HeapEntry last = data[--size];
		//sift down
		int i = 0;
		while (true) {
			int child = 2 * i + 1;
			if (child >= size)
				break;
			if (child + 1 < size && less(data[child + 1], data[child]))
				child++;
			if (!less(data[child], last))
				break;
			data[i] = data[child];
			i = child;
		}
		if (size > 0)
			data[i] = last;
		return top;
	}
private:
	HeapEntry* data;
	int size;
	int capacity;

	static bool less(const HeapEntry& a, const HeapEntry& b) {
		return a.cost < b.cost || (a.cost == b.cost && a.id < b.id);
	}
	void grow() {
		capacity *= 2;
		HeapEntry* bigger = new HeapEntry[capacity];
		for (int i = 0; i < size; i++)
			bigger[i] = data[i];
		delete[] data;
		data = bigger;
	}
};
