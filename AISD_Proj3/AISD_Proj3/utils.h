#pragma once
#include <iostream>

struct my_pair {
	int vertex;
	int degree;

};
int comp(const void* elem1, const void* elem2);
int compare_vertices_by_degree(const void* a, const void* b);
struct list_node;
struct simple_sorted_list {
	list_node* head;
	list_node* tail;
	simple_sorted_list();
	~simple_sorted_list();
	void add(int vertex);
	void print();
};
