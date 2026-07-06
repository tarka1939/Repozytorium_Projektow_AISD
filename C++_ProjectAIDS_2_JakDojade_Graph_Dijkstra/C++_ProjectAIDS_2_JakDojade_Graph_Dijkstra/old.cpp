//using namespace std;
//#include <iostream>
//#include "Graph.h"
//void main() {
//
//
//	Graph graph;
//	int sizeX, sizeY;
//	cin >> sizeX >> sizeY;
//	char** map = new char* [sizeY];
//	for (int i = 0; i < sizeY; i++)
//	{
//		map[i] = new char[sizeX];
//		cin >> map[i];
//	}
//	for (int i = 0; i < sizeY; i++)
//	{
//		for (int j = 0; j < sizeX; j++) {
//			if (map[i][j] == '#') {
//				if (map[i][j + 1] == '#' && j < sizeX - 1) {
//					graph.AddNode(Node<>(map[i][j], 0));
//				}
//				else if (map[i][j - 1] == '#' && j > 0) {
//					graph.AddNode(Node<>(map[i][j], 0));
//				}
//				else if (map[i + 1][j] == '#' && i < sizeY - 1) {
//					graph.AddNode(Node<>(map[i][j], 0));
//				}
//				else if (map[i - 1][j] == '#' && i > 0) {
//					graph.AddNode(Node<>(map[i][j], 0));
//				}
//			}
//		}
//	}
//}
//
//
//
//
//
//
//
