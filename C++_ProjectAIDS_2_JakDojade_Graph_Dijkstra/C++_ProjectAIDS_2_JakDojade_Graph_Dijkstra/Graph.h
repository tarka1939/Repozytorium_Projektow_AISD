#pragma once
#include "Node.h"
//#include <unordered_map>
//#include "fstream"
struct cell {
	int visited=-1;
	char ascii;
};
class Graph
{
public:
	void FloodFill(cell** map, int& sizeX, int& sizeY, Node<char*>& startnode);
	void FindConnections(cell** &map, int sizeX, int sizeY, Node<char*>& second);
	Graph();
	~Graph();
	void AddNode(Node<char*> second);
	void CreateGraph(char** &map, int sizeX, int sizeY, int nodes);
	Node<char*>*  GetNode(char* data);
	void PrintShortestPath(char* node1, char* node2, bool listPath);
private:
	int nodesChecked=0;
	//std::ofstream outfile;
	void ResetVisits();		
	int nodesNum=0;
	unordered_map<int, Node<char*>> Nodes;
	//HashMap<Node<char*>>* Nodes;
};
