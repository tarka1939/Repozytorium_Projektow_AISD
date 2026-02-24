#include "tree.h"

// Constructor
BalancingTree::BalancingTree() : root(nullptr) {}

// Height of a node
int BalancingTree::height(Node* node) {
    return node ? node->height : 0;
}

// Balance factor of a node
int BalancingTree::getBalance(Node* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

// Right rotation
BalancingTree::Node* BalancingTree::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Left rotation
BalancingTree::Node* BalancingTree::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Insert a node
BalancingTree::Node* BalancingTree::insert(Node* node, int key) {
    if (!node) return new Node(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
    {
		node->repetitions++;
        return node; // Duplicate keys are not allowed in the AVL tree
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rotateRight(node);

    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);

    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Reverse in-order traversal
void BalancingTree::reverseInOrder(Node* root) {
    if (root) {
        reverseInOrder(root->right);
        for(int i =0; i<root->repetitions;i++){
            printf("%d ", root->key); 
        }
        reverseInOrder(root->left);
    }
}

int BalancingTree::max(int a, int b) {
    return (a > b) ? a : b;
}

void BalancingTree::insert(int key) {
    root = insert(root, key);
}

void BalancingTree::print() {
    reverseInOrder(root);
	printf("\n");
}

int BalancingTree::minimum() {
	Node* current = root;
	while (current->left) {
		current = current->left;
	}
	return current->key;
}

bool BalancingTree::find(int n) {
	Node* current = root;
	while (current) {
		if (current->key == n) {
			return true;
		}
		else if (current->key > n) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}
	return false;

}