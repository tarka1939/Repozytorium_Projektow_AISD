#pragma once
#include <iostream>
class BalancingTree {
private:
    struct Node {
        int key;
        Node* left;
        Node* right;
        int height;
		int repetitions;

        Node(int k) : key(k), left(nullptr), right(nullptr), height(1), repetitions(1) {}
    };

    Node* root;
    int height(Node* node);
    int getBalance(Node* node);
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    Node* insert(Node* node, int key);
    void reverseInOrder(Node* root);
    int max(int a, int b);

public:
    BalancingTree();
    void insert(int key);
    void print();
	int minimum();
	bool find(int n);
};
