#pragma once
#include "List.h"
template <typename T>
class BlockList {
    List<Block<T>> list;
    
public:
    int blocks = 1;

    T& operator[](int index) {

        if (index < 0)
        {
            for (int i = 0; i<blocks; i++) {
                index = index + list[i].size;
            }
        }
        for (int i = 0; true; i++) {
            Block<T> &current = list[i];
            if (index >= current.size && current.size != 0) {
                index -= current.size;
            }

            else {
                return  current.body[index];
                break;
            }
        }
    }
    
    void RemoveOnIndex(int index) {
        for (int i = 0; true; i++) {
            Block<T> &current = list[i];
            if (index >= current.size) {
                index -= current.size;
            }
            else {
                if (!current.RemoveValue(index)) {
                    list.Delete(i);
                }
                break;
            }
        }
    }
    void AddValue(T value) {
        if (!list[blocks-1].AddValue(value)) {
            blocks++;
            
        }
    }
};