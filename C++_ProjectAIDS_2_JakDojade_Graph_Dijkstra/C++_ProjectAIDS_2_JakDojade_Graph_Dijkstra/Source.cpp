using namespace std;
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include "Graph.h"
#include <fstream>
//function that counts * appearances in 2d array

int CountStars(char** map, int sizeX, int sizeY) {
	int stars = 0;
	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			if (map[i][j] == '*')
				stars++;
		}
	}
	return stars;
}
void AddFlight(Graph& graph, char* city1, char* city2, int length) {
	if (graph.GetNode(city1)->GetLengthTo(city2) > length) {
		graph.GetNode(city1)->NewConnection(graph.GetNode(city2), length);
		//graph.GetNode(city2)->NewConnection(graph.GetNode(city1), length);
	}
}

int main(int argc, char* argv[]) {
	//fstream infile;
	//infile.open("tests/3.in");
	//cin.rdbuf(infile.rdbuf());
 //
	//done:
	//0 - V
	//1 - V
	//2 - V
	//3 - V
	//4 - V
	//5 - V
	//6 - V
	//7 - V
	//8 - V
	//9 - V
	//10 - X - Przekroczony limit czasu
	//11 - V
	//12 - X - Przekroczony limit czasu
	//13 - V - 300MB RAM :/

	
	Graph graph;
	int sizeX, sizeY;
	cin >> sizeX >> sizeY;
	cin.ignore();
	auto map = new char* [sizeY];
	for (int i = 0; i < sizeY; i++)
	{
		map[i] = new char[sizeX];
		//read whole line into map[i] using cin.getline
		cin.getline(map[i], sizeX + 1);
	}
	int nodes = CountStars(map, sizeX, sizeY);
	graph.CreateGraph(map, sizeX, sizeY, nodes);
	int flights;
	cin >> flights;
	for (int i = 0; i < flights; i++)
	{
		char city1[20];
		char city2[20];
		int length;
		
		cin >> city1>>city2>>length;
		//cout << city1<<endl;
		//cout << city2<<endl;
		//cout << length<<endl;
		AddFlight(graph, city1, city2, length);
	}
	int paths;
	cin >> paths;
	
	for (int i = 0; i < paths; i++)
	{
		char city1[20];
		char city2[20];
		int listing;
		cin >> city1 >> city2 >> listing;
		if(strcmp(city1,city2)==0)
			cout << 0 << endl;
		else
			graph.PrintShortestPath(city1, city2, bool(listing));
	}
}





