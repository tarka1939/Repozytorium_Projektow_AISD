#include <iostream>
// A class to store a queue
template <typename T>
class Queue
{
    T* arr;       // array to store queue elements
    int capacity;   // maximum capacity of the queue
    int front;      // front points to the front element in the queue (if any)
    int rear;       // rear points to the last element in the queue
    int count;      // current size of the queue

public:
    // Constructor to initialize a queue
    Queue(int size)
    {
        arr = new T[size];
        capacity = size;
        front = 0;
        rear = -1;
        count = 0;
    }

    // Destructor to free memory allocated to the queue
    ~Queue() {
        delete[] arr;
    }

    // Utility function to dequeue the front element
    T Dequeue()
    {
        T x = arr[front];
        front = (front + 1) % capacity;
        count--;
        return x;
    }

    // Utility function to add an item to the queue
    void Enqueue(T item)
    {
        rear = (rear + 1) % capacity;
        arr[rear] = item;
        count++;
    }

    // Utility function to return the front element of the queue
    T peek()
    {
        return arr[front];
    }

    // Utility function to return the size of the queue
    int size() {
        return count;
    }

    // Utility function to check if the queue is empty or not
    bool IsEmpty() {
        return (size() == 0);
    }

    // Utility function to check if the queue is full or not
    bool IsFull() {
        return (size() == capacity);
    }
};