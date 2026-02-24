//#include "head.h"
#include <fstream>
#include <string>
#include <ctime>
#include "Graph.h"
#include <fcntl.h>

using namespace std;

void readGraphToMatrix(int** graph, int n);
void readGraphToList(int** graph, int n);
void debug_PrintGraph_m(int** graph, int n);
void convert_l_to_m(int** graph, int n, int** graph_m);
void do_matrix() {
	int** graph_m = new int*;
	int n = 0;
	int m = 1;
	scanf("%d", &n);
	for (int j = 0; j < n; j++) {
		
		scanf("%d", &m);
		graph_m = new int* [m];
		for (int i = 0; i < m; i++) {
			graph_m[i] = new int[i];
			memset(graph_m[i], 0, i * sizeof(int));
		}
		{
			//debug_PrintGraph_m(graph_m, m);
			readGraphToMatrix(graph_m, m);
			debug_PrintGraph_m(graph_m, m);
			//1 OK
			printDegreeSequence_m(graph_m, m);
			//cout << "?" << endl;

			//2 OK
			printNumberOfComponents_m(graph_m, m);
			//cout << "?" << endl;

			//3 OK
			printIsBipartite_m(graph_m, m);
			//cout << "?" << endl;

			//4 OK
			printEccentricityOfVertices_m(graph_m, m);
			//cout << "?" << endl;

			//5 ?
			cout << "?" << endl;

			//6a OK
			printVerticesColours_Greedy_m(graph_m, m);
			///cout << "?" << endl;
			//printf("?\n");

			//6b OK
			printVerticesColours_LF_m(graph_m, m);
			//cout << "?" << endl;
			//printf("?\n");

			//6c OK
			printVerticesColours_SLF_m(graph_m, m);
			//cout << "?" << endl;
			//printf("?\n");

			//7 OK (slow)
			printNumOfC4Subgraphs_m(graph_m, m);
			//cout << "?" << endl;

			//8 OK
			printNumOfGraphComplementsEdges_m(graph_m, m);
			//cout << "?" << endl;
		}

		memset(graph_m, 0, m * sizeof(int));
	}
	delete[] graph_m;
}
void do_list() {
	
	int n = 0;
	//cin >> n;
	scanf("%d", &n);
	int m = 0;
	for (int i = 0; i < n; i++)
	{
		
		int** components = new int*;
		scanf("%d", &m);
		int** graph = new int* [m + 1];
		graph[0] = new int[2];
		graph[0][0] = m;
		graph[0][1] = 1;
		{
			readGraphToList(graph, m);
			//1 OK
			printDegreeSequence_l(graph, m);
			//cout << "?" << endl;

			//2 OK
			printNumberOfComponents_l(graph, m, components);
			//cout << "?" << endl;

			//3 OK
			printIsBipartite_l(graph, m);
			//cout << "?" << endl;

			//4 OK
			printEccentricityOfVertices_optimized(graph, m, components);
			//cout << "?" << endl;

			//5 ?
			cout << "?" << endl;

			//6a OK
			printVerticesColours_Greedy_l(graph, m);
			//cout << "?" << endl;

			//6b OK
			printVerticesColours_LF_l(graph, m);
			//cout << "?" << endl;

			//6c OK
			printVerticesColours_SLF_l(graph, m, components);
			//cout << "?" << endl;

			//7 OK (slow)
			//printNumOfC4Subgraphs_l(graph, m, components);
			printNumOfC4Subgraphs_optimized(graph, m);
			//cout << "?" << endl;

			//8 OK
			printNumOfGraphComplementsEdges_l(graph, m);
			//cout << "?" << endl;
		}
		//delete graph and components
		memset(components, 0, graph[0][1] * sizeof(int));
		memset(graph, 0, m * sizeof(int));
		delete[] graph;
		delete components;
	}
	
}

std::string test_list[] = {
	"test_2p_in",
	"test_10_in",
	"test_20_in",
	"test_Pl_in",
	//"4",
	//"5",
	//"6", 
	//"7",
	//"11", 
	//"16"
};
void tester() {
	//tester

	auto old_cout = cout.rdbuf();
	auto old_cin = cin.rdbuf();
	for (std::string test : test_list) {
		//start timer 
		cout << test + ".txt" << std::endl;
		ifstream fileIn(test + ".txt");
		ofstream fileOut("my_" + test + "_list.out");		
		// Redirecting cin to read from "input.txt" 
		cin.rdbuf(fileIn.rdbuf());
		// Redirecting cout to write to "output.txt" 
		cout.rdbuf(fileOut.rdbuf());
		//mainLoop();
		clock_t start = clock();
		do_list();
		clock_t end = clock();
		cout.rdbuf(old_cout);
		cin.rdbuf(old_cin);
		cout << "done" << std::endl;
		cout << "List time: " << (double)(end - start) / CLOCKS_PER_SEC << std::endl;
		ofstream fileOut2("my_" + test + "_matrix.out");
		// Redirecting cin to read from "input.txt" 
		cin.rdbuf(fileIn.rdbuf());
		// Redirecting cout to write to "output.txt" 
		cout.rdbuf(fileOut2.rdbuf());
		//mainLoop();
		start = clock();
		do_matrix();
		//end timer
		end = clock();
		cout.rdbuf(old_cout);
		cin.rdbuf(old_cin);
		cout << "done" << std::endl;
		cout << "Matrix time: " << (double)(end - start) / CLOCKS_PER_SEC << std::endl;
	}
	char* test = new char[100];
	cin >> test;
	delete[] test;
}
int main() {
	//tester();
	do_list();
	//do_matrix();
}

void debug_PrintGraph_m(int** graph, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			//cout << graph[i][j] << " ";
			printf("%d ", graph[i][j]);
		}
		//cout << endl;
		printf("\n");
	}
}
void debug_PrintGraph_l(int** graph, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 1; j < graph[i][0] + 1; j++) {
			cout << graph[i][j] << " ";
		}
		cout << endl;
	}

}
void readGraphToMatrix(int** graph, int n) {
	int m, o;
	for (int i = 0; i < n; i++) {
		scanf("%d", &m);
		for (int j = 0; j < m; j++) {
			scanf("%d", &o);
			if (o-1 < i)
				graph[i][o-1] = 1;
			else if ((o-1) == i)
				graph[i][i] = 0;
			else
				graph[o-1][i] = 1;
			
		}
	}
}

void readGraphToList(int** graph, int n) {
	int m, o;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &m);
		//cin >> m;
		graph[i] = new int[m+1];
		graph[i][0] = m;
		for (int j = 1; j < m+1; j++) {
			//cin >> o;
			scanf("%d", &o);
			graph[i][j] = o;
		}
	}
}

void convert_l_to_m(int** graph, int n, int** graph_m) {
	graph_m = new int* [n];
	for (int i = 0; i < n; i++) {
		graph_m[i] = new int[n-i];
		memset(graph_m[i], 0, (n - i) * sizeof(int));
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < graph[i][0] + 1; j++) {
			int cell;
			if (i > j)
				cell = graph[i][j];
			else if (i == j)
				cell = 0;
			else
				cell = graph[j][i];
			graph_m[i - 1][j - 1] = cell;
		}
	}
}