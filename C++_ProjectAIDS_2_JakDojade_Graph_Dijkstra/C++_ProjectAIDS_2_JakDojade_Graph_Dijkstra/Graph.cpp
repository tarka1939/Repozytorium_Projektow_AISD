#include "Graph.h"
#include "iostream"
#include "Queue.h"
struct queueNode {
	int x;
	int y;
	int steps;

	queueNode() {
		x = -1;
		y = -1;
		steps = -1;
	};
	queueNode(int x, int y, int steps) : x(x), y(y), steps(steps) {};
};/*
struct Queue {
	queueNode* arr;
	int size;
	int front;
	int rear;
	~Queue() {
		delete[] arr;
	}
	Queue(int size) {
		this->size = size;
		front = rear = -1;
		arr = new queueNode[size];
	}
	void Enqueue(int x, int y, int steps) {
		if (front == -1)
			front = 0;
		rear++;
		queueNode node(x, y, steps);
		arr[rear] = node;
	}
	queueNode Dequeue() {
		queueNode node = arr[front];
		front++;
		if (front > rear)
			front = rear = -1;
		return node;
	}
	bool IsEmpty() {
		return front == -1;
	}

};*/


void FindCityName(cell** map, int x, int y, int sizeX, int sizeY, char* name);

//floodfill algorithm that is marking visited nodes
void Graph::FloodFill(cell** map,int &sizeX, int &sizeY, Node<char*>& startnode)
{
	int x = startnode.mapX;
	int y = startnode.mapY;
	bool worthit = false;
	
		if (y < sizeY - 1 && (map[y + 1][x].ascii == '#' || map[y + 1][x].ascii == '*'))
		{
			worthit = true;
		}
		else if (y > 0 && (map[y - 1][x].ascii == '#' || map[y - 1][x].ascii == '*'))
		{
			worthit = true;
		}
		else if (x < sizeX - 1 && (map[y][x + 1].ascii == '#' || map[y][x + 1].ascii == '*'))
		{
			worthit = true;
		}
		else if (x > 0 && (map[y][x - 1].ascii == '#' || map[y][x - 1].ascii == '*'))
		{
			worthit = true;
		}
	
	if (!worthit)
		return;

	Queue<queueNode> queue(sizeX*sizeY);
	
	queue.Enqueue(queueNode(startnode.mapX, startnode.mapY, 0));
	map[startnode.mapY][startnode.mapX].visited = nodesChecked;
	while (!queue.IsEmpty()) {


		//print 2d map for debug
		/*for (int i = 0; i < sizeY; i++)
		{
			for (int j = 0; j < sizeX; j++)
			{
				if (map[i][j].visited==nodesChecked)
					std::cout << "X";
				else
					std::cout << map[i][j].ascii;
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;*/


		queueNode node = queue.Dequeue();
		int steps = node.steps;
		int x = node.x;
		int y = node.y;

		if (map[y][x].ascii == '*' && steps != 0)
		{
			char* name = new char[20];
			for (size_t i = 0; i < 20; i++)
			{
				name[i] = '\0';
			}
			FindCityName(map, x, y, sizeX, sizeY, name);
			//Node <char*>* newNode = &Nodes[Hash(name)];
			//if there is no existing connection in node.connections to newNode, call NewConnection, else check if steps are lower than existing connection length
			bool containsHash = false;
			for (auto& it : startnode.connections)
			{
				if (it.first == Hash(name))
				{
					containsHash = true;
					break;
				}
			}

			if (!containsHash)
			{

				startnode.NewConnection(&Nodes[Hash(name)], steps);

				//std::cout << "New connection between " << startnode.data << " and " << Nodes[Hash(name)].data << " with " << steps << " steps" << std::endl;
			}
			else if (startnode.connections[Hash(name)].length > steps)
			{
				startnode.connections[Hash(name)].length = steps;

				//std::cout << "Connection changed between " << startnode.data << " and " << name << " with " << steps << " steps" << std::endl;
			}
			delete[] name;
		}

		else {
			steps++;
			if (y < sizeY - 1 && map[y + 1][x].visited < nodesChecked && (map[y + 1][x].ascii == '#' || map[y + 1][x].ascii == '*'))
			{
				map[y+1][x].visited = nodesChecked;
				queue.Enqueue(queueNode(x, y + 1, steps));
			}
			if (y > 0 && map[y - 1][x].visited < nodesChecked && (map[y - 1][x].ascii == '#' || map[y - 1][x].ascii == '*'))
			{
				map[y-1][x].visited = nodesChecked;
				queue.Enqueue(queueNode(x, y - 1, steps));
			}
			if (x < sizeX - 1 && map[y][x + 1].visited < nodesChecked && (map[y][x + 1].ascii == '#' || map[y][x + 1].ascii == '*'))
			{
				map[y][x+1].visited = nodesChecked;
				queue.Enqueue(queueNode(x + 1, y, steps));
			}
			if (x > 0 && map[y][x - 1].visited<nodesChecked && (map[y][x - 1].ascii == '#' || map[y][x - 1].ascii == '*'))
			{
				map[y][x-1].visited = nodesChecked;
				queue.Enqueue(queueNode(x - 1, y, steps));
			}
		}
	}
}


void Graph::FindConnections(cell** &map, int sizeX, int sizeY, Node<char*> &startnode)
{
	//reset visited nodes on map
	/*for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			map[i][j].visited = false;
		}
	}*/
	
	FloodFill(map, sizeX, sizeY, startnode);

}

Graph::Graph()
{
    nodesNum = 0;
}

Graph::~Graph()
{

}

void Graph::AddNode(Node<char*> second)
{
	Nodes[Hash(second.data)] = second;
}

void Graph::ResetVisits()
{
    //iterate over std unordered_map and call ResetVisited() on all nodes
	for (auto &x : Nodes)
	{
		x.second.ResetVisited();
	}
}

//funtion that uses dijkstra algorithm to find shortest path between two nodes using adjacency matrix with weights
void Graph::PrintShortestPath(char* node1, char* node2, bool listPath) {
	struct NodeData
	{
		Node<char*> *node = NULL;
		int id;
		int cost=100000000;
		int Path;
		bool Known=false;
	};
	int node1ID;
	int node2ID;
	int* visitedNodes= new int[nodesNum];
	for (int i = 0; i < nodesNum; i++)
	{
		visitedNodes[i] = -1;
	}
	NodeData* nodes_D = new NodeData[nodesNum];
	for (auto &x : Nodes) {
		nodes_D[x.second.id].node = &x.second;
		nodes_D[x.second.id].id = x.second.id;
	}


	node1ID = Nodes[Hash(node1)].id;
	node2ID = Nodes[Hash(node2)].id;
	NodeData* current = &nodes_D[node1ID];
	nodes_D[node1ID].cost = 0;
	NodeData* shortest=current;
	while (!nodes_D[node2ID].Known) {
		current = shortest;
		current->Known = true;
		int costOfMove = current->cost;
		for (auto c : current->node->connections) {
			if (nodes_D[c.second.node->id].cost > costOfMove + c.second.length)
			{
				nodes_D[c.second.node->id].cost = costOfMove + c.second.length;
				nodes_D[c.second.node->id].Path = current->id;
			}

		}
		int nextmovecost = 10000000;
		for (int i = 0; i < nodesNum; i++)
		{
			if (nodes_D[i].Known == false && nodes_D[i].cost < nextmovecost)
			{
				nextmovecost = nodes_D[i].cost;
				shortest = &nodes_D[i];
			}
		}
	}
	std::cout<<nodes_D[node2ID].cost;
	//outfile<< nodes_D[node2ID].cost;
	
	if (listPath) {
		char** path = new char* [nodesNum];
		int pathLen = 0;
		//print path from node2 to node1
		int currentID = node2ID;
		while (currentID != node1ID)
		{
			path[pathLen] = nodes_D[currentID].node->data;
			currentID = nodes_D[currentID].Path;
			pathLen++;
		}
		for (int i = pathLen - 1; i > 0; i--)
		{
			std::cout << " " << path[i];
			//outfile << " " << path[i];
		}
		delete [] path;
	}
	std::cout << std::endl;
	//outfile << std::endl;
	delete [] nodes_D;
	delete [] visitedNodes;
};


void FindCityName(cell** map, int x, int y, int sizeX, int sizeY, char* name)
{
	//find which of aligned 8 tiles contains a letter
	int firstLetterX, firstLetterY;
	firstLetterX = x;
	firstLetterY = y;
	bool foundL = false;
	for (int i = -1; i < 2 && !foundL; i++) {
		for (int j = -1; j < 2; j++)
		{
			if (x + i >= 0 && x + i < sizeX && y + j >= 0 && y + j < sizeY)
			{
				if (map[y + j][x + i].ascii != '*'&& map[y + j][x + i].ascii != '.'&& map[y + j][x + i].ascii != '#')
				{
					firstLetterX = x + i;
					firstLetterY = y + j;
					foundL = true;
					break;
				}
			}
		}
	}
	//Check if there are more letters on the left of the first letter

	while (firstLetterX-1>=0 && map[firstLetterY][firstLetterX-1].ascii != '*' && map[firstLetterY][firstLetterX-1].ascii != '.' && map[firstLetterY][firstLetterX-1].ascii != '#')
	{
		firstLetterX--;
	}
	//Read all letters to the right of the first letter
	int i = 0;
	while (firstLetterX + i < sizeX && map[firstLetterY][firstLetterX + i].ascii != '*' && map[firstLetterY][firstLetterX + i].ascii != '.' && map[firstLetterY][firstLetterX + i].ascii != '#')
	{
		name[i] = map[firstLetterY][firstLetterX + i].ascii;
		i++;
	}

};
void Graph::CreateGraph(char** &map, int sizeX, int sizeY, int nodes) {
	//outfile.open("output.out");
	cell** c_map = new cell * [sizeY];
	for (int i = 0; i < sizeY; i++)
	{
		c_map[i] = new cell[sizeX];
	}
	//Nodes = new HashMap<Node<char*>>(nodes);
	//create cell map
	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++)
		{
			c_map[y][x].ascii = map[y][x];
		}
	}
	for (int x = 0; x < sizeX; x++) {
		for (int y = 0; y < sizeY; y++) {
			if (map[y][x] == '*') {
				char* name = new char[20];
				for (size_t i = 0; i < 20; i++)
				{
					name[i] = '\0';
				}
				FindCityName(c_map, x, y, sizeX, sizeY, name);
				//std::cout <<"Output: " << name<<std::endl;
				Node<char*>* node = new Node<char*>(name, nodesNum);
				node->setMapX(x);
				node->setMapY(y);
				AddNode(*node);
				nodesNum++;

			}
		}
	}
	//find connections for all nodes in graph

	for (auto &x : Nodes)
	{	
		FindConnections(c_map, sizeX, sizeY, x.second);
		nodesChecked++;
	}
}

Node<char*>* Graph::GetNode(char* data)
{
	return &Nodes[Hash(data)];
}
