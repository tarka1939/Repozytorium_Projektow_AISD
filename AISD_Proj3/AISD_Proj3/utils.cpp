#include "utils.h"
int comp(const void* elem1, const void* elem2)
{
	int f = *((int*)elem1);
	int s = *((int*)elem2);
	if (f < s) return  1;
	if (f > s) return -1;
	return 0;
}
int compare_vertices_by_degree(const void* a, const void* b) {
	struct my_pair* p1 = (struct my_pair*)a;
	struct my_pair* p2 = (struct my_pair*)b;
	if (p1->degree < p2->degree) return 1;
	if (p1->degree > p2->degree) return -1;
	if (p1->degree == p2->degree) {
		if (p1->vertex > p2->vertex) return 1;
		if (p1->vertex < p2->vertex) return -1;
	}
	return 0;
}

struct list_node {
	int vertex;
	list_node* next;
	list_node(int vertex, list_node* next) {
		this->vertex = vertex;
		this->next = next;
	}
};

	
simple_sorted_list::simple_sorted_list() {
	head = nullptr;
	tail = nullptr;
};
simple_sorted_list::~simple_sorted_list() {
	while (head != nullptr) {
		list_node* temp = head;
		head = head->next;
		delete temp;
	}
};
void simple_sorted_list::add(int vertex) {
	list_node* new_node = new list_node{ vertex, nullptr };
	if (head == nullptr) {
		head = new_node;
		tail = new_node;
	}
	else {
		list_node* current = head;
		list_node* prev = nullptr;
		while (current != nullptr && current->vertex > vertex) {
			prev = current;
			current = current->next;
		}
		if (prev == nullptr) {
			new_node->next = head;
			head = new_node;
		}
		else if (current == nullptr) {
			tail->next = new_node;
			tail = new_node;
		}
		else {
			prev->next = new_node;
			new_node->next = current;
		}
	}
};
void simple_sorted_list::print() {
	list_node* current = head;
	while (current != nullptr) {
		//cout << current->vertex << " ";
		printf("%d ", current->vertex);
		current = current->next;
	}
	//cout << endl;
	printf("\n");
};