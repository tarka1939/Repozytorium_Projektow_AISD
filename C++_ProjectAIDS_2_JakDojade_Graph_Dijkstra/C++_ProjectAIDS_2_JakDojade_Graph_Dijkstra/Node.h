#pragma once
#include "utils.h"
//#include "HashMap.h"
#include <unordered_map>
template <typename T = int>
struct Node {
	
public:
	int id;

	void NewConnection(Node* node, int length) {

		connections[Hash(node->data)] = Connection(node, length);
	}
	void ResetVisited() {
		visited = false;
	}
	Node() {
		visited = false;
	}
	Node(T data, int id) {
		this->id = id;
		this->data = data;
		visited = false;
	}
	void setMapX(int x) {
		mapX = x;
	}
	void setMapY(int y) {
		mapY = y;
	}
	int getMapX() {
		return mapX;
	}
	int getMapY() {
		return mapY;
	}
	T& getData() {
		return data;
	}
	friend class Graph;
	int GetLengthTo(char* city) {
		return connections[Hash(city)].length;
	}
private:
	T data;
	struct Connection {
		Node* node;
		int length=100000000;
		Connection(Node* node, int length) : node(node), length(length) {}
		Connection() {};
	};
	int mapX, mapY;
	unordered_map <int, Connection> connections;
	bool visited;
};