#include "Graph.h"
//1
void printDegreeSequence_m(int** graph, int n) {
	//print sorted degree sequence
	simple_sorted_list list;
	
	for (int i = 1; i < n-1; i++) {
		int degree = 0;
		for (int j = 0; j < n-1; j++) {
			if (i > j)
			degree += graph[i][j];
			else if(i==j)
				degree += 0;
			else
				degree += graph[j][i];
			//printf("degree: %d ", degree);
		}
		list.add(degree);
	}

	list.print();
	
	//cout << endl;
	//printf("\n");
	//delete[] degree;
}

void debug_printVisited(int x, int y, int* visited, int** board, int n) {
	cout << "Visited: ";
	for (int i = 0; i < n; i++) {
		cout << visited[i] << " ";
	}
	cout << endl;
	cout << "Board: " << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i + 1; j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
	cout << "x: " << x << " y: " << y << endl;
	cout << "-----------------" << endl;
}

//2
void printNumberOfComponents_m(int** graph, int n) {
	//number of non connected sub graphs
	int* visited = new int[n];
	int* queue = new int[n + 1];

	int count = 1;

	for (int i = 0; i < n; i++) {
		visited[i] = 0;
	}

	queue[0] = 0;
	int front = 0;
	int rear = 1;
	visited[0] = 1;
check_subgraph:
	while (front < rear) {

		int u = queue[front];

		front++;
		for (int i = 0; i < n; i++) {
			int cell;
			if (u > i)
				cell = graph[u][i];
			else if (u == i)
				cell = 0;
			else
				cell = graph[i][u];
			//printf("degree: %d ", degree);
			if (cell == 1 && visited[i] == 0) {
				visited[i] = 1;
				//debug_printVisited(u, i, visited, graph, n);
				queue[rear] = i;
				rear++;
			}
		}
	}
	//check if all vertices are visited
	int flag = 0;
	for (int i = 0; i < n; i++) {
		if (visited[i] == 0) {
			flag = 1;
			break;
		}
	}
	if (flag == 1) {
		count++;
		for (int i = 0; i < n; i++) {
			if (visited[i] == 0) {
				visited[i] = 1;
				queue[rear] = i;
				rear++;
				goto check_subgraph;
			}
		}
	}
	//cout << count << endl;
	printf("%d\n", count);
	delete[] visited;

}

//3
void printIsBipartite_m(int** graph, int n) {
	int* colour = new int[n];
	for (int i = 0; i < n; ++i)
		colour[i] = -1;

	colour[0] = 1;
	int* queue = new int[n];
	int front = 0, rear = 0;
	queue[rear++] = 0;

	while (front != rear) {
		int u = queue[front++];
		for (int v = 0; v < n; ++v) {
			int cell;
			if (u > v)
				cell = graph[u][v];
			else if (u == v)
				cell = 0;
			else
				cell = graph[v][u];
			if (cell && colour[v] == -1) {
				colour[v] = 1 - colour[u];
				queue[rear++] = v;
			}
			else if (cell && colour[v] == colour[u])
			{
				//cout << "F" << endl;
				printf("F\n");
				delete[] colour;
				delete[] queue;

				return;
			}
		}
	}
	//cout << "T" << endl;
	printf("T\n");
	delete[] colour;
	delete[] queue;
}

//4
void printEccentricityOfVertices_m(int** graph, int n) {
	//eccentricity is the maximum distance from a vertex to any other vertex

	int* visited = new int[n];
	int* distance = new int[n];
	int* queue = new int[n];
	for (int i = 0; i < n; i++) {
		visited[i] = 0;
	}
	for (int i = 0; i < n; i++) {
		int eccentricity = 0;
		for (int j = 0; j < n; j++) {
			distance[j] = 0;
		}

		int front = 0;
		int rear = 0;
		queue[rear] = i;
		rear++;
		visited[i] = i + 1;
		while (front < rear) {
			int u = queue[front];
			front++;
			for (int j = 0; j < n; j++) {
				int cell;
				if (u > j)
					cell = graph[u][j];
				else if (u == j)
					cell = 0;
				else
					cell = graph[j][u];
				if (cell == 1 && visited[j] < (i + 1)) {
					visited[j] = i + 1;
					distance[j] = distance[u] + 1;
					queue[rear] = j;
					rear++;
				}
			}
			if (distance[u] > eccentricity)
				eccentricity = distance[u];
		}
		//cout << eccentricity << " ";
		printf("%d ", eccentricity);
	}
	//cout << endl;
	printf("\n");
	delete[] visited;
	delete[] distance;
	delete[] queue;
}

//5
void printIsPlanar_m(int** graph, int n) {
	//check number of edges and vertices
	int edges = 0;
	int vertices = n;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			int cell;
			if (i > j)
				cell = graph[i][j];
			else if (i == j)
				cell = 0;
			else
				cell = graph[j][i];
			if (graph[i][j] == 1) {
				edges++;
			}
		}
	}
	if (edges > 3 * vertices - 6) {
		cout << "F" << endl;
	}
	else {
		if (isSubgraphHomeomorphicToK5_m(vertices, graph)) {
			cout << "F" << endl;
		}
		else if (isSubgraphHomeomorphicToK33_m(vertices, graph)) {
			cout << "F" << endl;
		}
		else
			cout << "T" << endl;
	}
}

bool isSubgraphHomeomorphicToK5_m(int n, int** graph)
{
	// Check for every combination of 5 vertices
	for (int a = 0; a < n; a++) {
		for (int b = a + 1; b < n; b++) {
			for (int c = b + 1; c < n; c++) {
				for (int d = c + 1; d < n; d++) {
					for (int e = d + 1; e < n; e++) {
						int vertices[5] = { a, b, c, d, e };
						bool isK5 = true;
						for (int i = 0; i < 5; i++) {
							for (int j = i + 1; j < 5; j++) {
								if (!graph[vertices[i]][vertices[j]]) {
									isK5 = false;
									break;
								}
							}
							if (!isK5) break;
						}
						if (isK5) return true;
					}
				}
			}
		}
	}
	return false;
}

bool isSubgraphHomeomorphicToK33_m(int n, int** graph)
{
	return false;
}


bool isSafe(int v, int** graph, int* colour, int c, int n) {
	for (int i = 0; i < n; ++i) {
		int cell;
		if (v > i)
			cell = graph[v][i];
		else if (i == v)
			cell = 0;
		else
			cell = graph[i][v];
		if (cell && c == colour[i])
			return false;
	}
	return true;
}


bool graphcolouringUtil(int** graph, int* colour, int v, int V) {
	if (v == V)
		return true;

	for (int c = 1;; c++) {
		if (isSafe(v, graph, colour, c, V)) {
			colour[v] = c;
			if (graphcolouringUtil(graph, colour, v + 1, V))
				return true;
			colour[v] = 0; // Backtracking
		}
	}
	return false;
}

//6a
void printVerticesColours_Greedy_m(int** graph, int n) {
	int* colour = new int[n]();

	graphcolouringUtil(graph, colour, 0, n);

	for (int i = 0; i < n; ++i)
		cout << colour[i] << " ";

	cout << endl;

	delete[] colour;
}

bool graphcolouringUtil_LF(int** graph, int* colour, int* order, int current, int num, int V) {
	//print debug info:
	//cout << "Current: " << current << " Num: " << num << endl;
	//for (int i = 0; i < V; i++) {
	//	cout << order[i] << " ";
	//}
	//cout << endl;
	//for (int i = 0; i < V; i++) {
	//	cout << colour[i] << " ";
	//}
	//cout << endl;
	//cout << "-----------------" << endl;

	if (num == V)
		return true;
	int next = order[++num];
	for (int c = 1;; c++) {
		if (isSafe(current, graph, colour, c, V)) {
			colour[current] = c;
			if (graphcolouringUtil_LF(graph, colour, order, next, num, V))
				return true;
			colour[current] = 0; // Backtracking
		}
	}
	return false;
}

//6b
void printVerticesColours_LF_m(int** graph, int size) {
	int* colour = new int[size];
	int* degrees = new int[size];
	int* vertices = new int[size];
	//sort vertices by degree
	memset(colour, 0, size * sizeof(int));
	memset(degrees, 0, size * sizeof(int));
	for (int i = 0; i < size; i++) {
		vertices[i] = i;
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			int cell;
			if (i > j)
				cell = graph[i][j];
			else if (i == j)
				cell = 0;
			else
				cell = graph[j][i];
			degrees[i] += cell;
		}
	}
	struct my_pair* vert = new struct my_pair[size];
	for (int i = 0; i < size; i++) {
		vert[i].vertex = vertices[i];
		vert[i].degree = degrees[vertices[i]];
	}
	qsort(vert, size, sizeof(my_pair), compare_vertices_by_degree);
	for (int i = 0; i < size; i++) {
		vertices[i] = vert[i].vertex;
	}
	int first = vertices[0];
	graphcolouringUtil_LF(graph, colour, vertices, first, 0, size);

	for (int i = 0; i < size; ++i)
		cout << colour[i] << " ";

	cout << endl;
	delete vert;
	delete[] degrees;
	delete[] vertices;
	delete[] colour;
}

//6c
void printVerticesColours_SLF_m(int** graph, int n) {
	int* colour = new int[n]();
	int* degrees = new int[n]();
	int* order = new int[n]();

	//sort vertices by degree
	for (int i = 0; i < n; i++) {
		degrees[i] = 0;
		order[i] = i;
		for (int j = 0; j < n; j++) {
			degrees[i] += graph[i][j];
		}
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n - 1; j++)
			if (degrees[j] < degrees[j + 1]) {
				int temp = degrees[j];
				degrees[j] = degrees[j + 1];
				degrees[j + 1] = temp;

				temp = order[j];
				order[j] = order[j + 1];
				order[j + 1] = temp;
			}

	//if multiple same degree vertices sort them by their number
	for (int i = 0; i < n - 1; i++) {
		if (degrees[i] == degrees[i + 1]) {
			if (order[i] > order[i + 1]) {
				int temp = order[i];
				order[i] = order[i + 1];
				order[i + 1] = temp;
			}
		}
	}

	int first = order[0];
	graphcolouringUtil_LF(graph, colour, order, first, 0, n);

	for (int i = 0; i < n; ++i)
		cout << colour[i] << " ";

	cout << endl;
	delete[] degrees;
	delete[] order;
	delete[] colour;

}

//7
void printNumOfC4Subgraphs_m(int** graph, int n) {
	int count = 0;
	// Iterate over all pairs of vertices (i, j)
	// Loop through all possible combinations of 4 vertices
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (graph[i][j]) {
				for (int k = 0; k < n; k++) {
					if (graph[j][k] && k != i) {
						for (int l = 0; l < n; l++) {
							if (graph[k][l] && l != j && l != i) {
								if (graph[l][i]) {
									count++;
								}
							}
						}
					}
				}
			}
		}
	}

	cout << count / 4 << endl;
}

//8
void printNumOfGraphComplementsEdges_m(int** graph, int n) {
	int count = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {

			if (graph[i][j] == 0) {
				count++;
			}
		}
	}
	cout << count << endl;
}