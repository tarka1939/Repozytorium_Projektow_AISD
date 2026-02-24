#include "Graph.h"
//#include <algorithm>
#include <stdlib.h>

bool tests[10] = {
	1, //1
	1, //2
	1, //3
	1, //4
	0, //5
	1, //6a
	1, //6b
	1, //6c
	1, //7
	1  //8
};

void printDegreeSequence_l(int** graph, int size) {
	//int* degrees = new int[size];
	//simple_sorted_list list;
	BalancingTree tree;
	// Count the degree of each vertex
	for (int i = 1; i <= size; ++i) {
		//degrees[i - 1] = graph[i][0];
		//list.add(graph[i][0]);
		tree.insert(graph[i][0]);
	}
	tree.print();
	//list.print();
	//delete &list;
	// Sort the degrees in descending order
	//std::sort(degrees, degrees + size, std::greater<int>());
	//qsort(degrees, size, sizeof(int), comp);

	// Print the sorted degree sequence
	//for (int i = 0; i < size; ++i) {
	//	//std::cout << degrees[i] << " ";
	//	printf("%d ", degrees[i]);
	//}
	//std::cout << std::endl;
	//printf("\n");

	// Free the allocated memory for degrees array
	//delete[] degrees;
}

void debug_printVisited_l(int x, int y, int* visited, int** board, int size) {
	cout << "Visited: ";
	for (int i = 0; i < size; i++) {
		cout << visited[i] << " ";
	}
	cout << endl;
	cout << "Board: " << endl;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < i + 1; j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
	cout << "x: " << x << " y: " << y << endl;
	cout << "-----------------" << endl;
}

struct stack {
	int* data;
	int size;
	int capacity;
	stack() {
		size = 0;
		capacity = 64;
		data = new int[capacity];
	}
	~stack() {
		delete[] data;
	}
	bool empty() {
		return size == 0;
	}
	int pop() {
		if (size == 0) {
			return -1;
		}
		return data[--size];
	}
	void push(int x) {
		if (size == capacity) {
			resize();
		}
		data[size++] = x;
	}
private:
	void resize() {
		int new_capacity = abs(capacity * (1 + log10(2)));
		int* new_data = new int[new_capacity];
		for (int i = 0; i < size; ++i) {
			new_data[i] = data[i];
		}

		delete[] data;
		data = new_data;
		capacity = new_capacity;
	}
};

void dfs(int** graph, int vertex, bool* visited, int size, int** &components,int* component_sizes ,int num_components) {
	struct stack s;
	int* temp = new int[size + 1];
	int componentSize = 1;
	s.push(vertex);
	temp[0] = vertex;
	while (!s.empty()) {
		int v = s.pop();
		if (!visited[v]) {
			temp[componentSize++] = v;
			visited[v] = true;
			for (int i = 1; i <= graph[v][0]; i++) {
				int neighbor = graph[v][i];
				if (!visited[neighbor]) {
					s.push(neighbor);
					
				}
			}
		}
	}
	components[num_components] = new int[componentSize];
	for (int i = 0; i < componentSize; i++) {
		components[num_components][i] = temp[i];
	}
	component_sizes[num_components] = componentSize;
	delete[] temp;
}

void bfs(int** graph, int vertex, int* visited, int size, int** &components, int* component_sizes, int numComponents) {
	int* queue = new int[size+1];
	int* temp = new int[size + 1];
	int componentSize = 0;
	int front = 0;
	int back = 0;
	queue[back++] = vertex;
	visited[vertex] = true;
	//cout << "Component: " << numComponents+1 << endl;
	while (front != back) {		
		//end of visiting 
		int v = queue[front++];
		temp[componentSize++] = v;
		//visiting vertex: v with neighbours: 
		/*cout << "Visiting vertex: " << v << " with neighbours: ";
		for (int i = 1; i <= graph[v][0]; i++) {
			cout << graph[v][i] << " ";
		}
		cout << endl;	*/					
			for (int i = 1; i <= graph[v][0]; i++) {
				int neighbour = graph[v][i];
				if (!visited[neighbour]) {
					//adding vertex to queue
					//cout << "Adding vertex: " << neighbor << " to queue" << endl;
					//front back
					//cout << "Front: " << front << " Back: " << back << endl;
					visited[neighbour] = true;
					queue[back++] = neighbour;
				}
			}
		
	}
	components[numComponents] = new int[componentSize];
	for (int i = 0; i < componentSize; i++) {
		components[numComponents][i] = temp[i];
	}
	component_sizes[numComponents] = componentSize;
	delete[] temp;
	delete[] queue;
}

//2
void printNumberOfComponents_l(int** graph, int size, int** &components) {
	int* visited = new int[size + 1];
	memset(visited, 0, (size + 1) * sizeof(int));
	int numComponents = 0;
	int* component_sizes = new int [size + 1];
	//int** temp = new int* [size+1];
	components = new int* [size+1];
	// Perform DFS for each vertex
	for (int i = 1; i <= size; i++) {
		if (!visited[i]) {
			
			//dfs(graph, i, visited, size, components ,component_sizes, numComponents);
			bfs(graph, i, visited, size, components, component_sizes, numComponents);
			numComponents++;
		}
	}
	graph[0][1] = numComponents;
	
	cout << numComponents << endl;
	//printf("%d\n", numComponents);
	components[numComponents] = new int[numComponents];
	for (int i = 0; i < numComponents; i++) {
		components[numComponents][i] = component_sizes[i];
	}

	/*for (int i = 0; i < numComponents; i++) {
		delete[] temp[i];
	}
	delete[] temp;*/
	
	delete[] visited;
	delete[] component_sizes;
}

//3
void printIsBipartite_l(int** graph, int size) {
	int* colours = new int[size + 1];
	for (int i = 1; i <= size; ++i) {
		colours[i] = 0;
	}

	int* queue = new int[size + 1];
	int front = 0;
	int back = 0;

	for (int start = 1; start <= size; ++start) {
		if (colours[start] == 0) {
			colours[start] = 1;
			queue[back++] = start;

			while (back!=front) {
				int u = queue[front++];

				for (int i = 1; i <= graph[u][0]; ++i) {
					int v = graph[u][i];
					if (colours[v] == 0) {
						colours[v] = (colours[u] == 1) ? 2 : 1;
						queue[back++] = v;
					}
					else if (colours[v] == colours[u]) {
						delete[] colours;
						delete[] queue;
						cout << "F" << endl;
						//printf("F\n");
						return; // Adjacent vertices have the same colour
					}
				}
			}
		}
	}
	cout << "T" << endl;
	//printf("T\n");
	delete[] queue;
	delete[] colours;
}

//4
void printEccentricityOfVertices_optimized(int** graph, int size, int** components) {
	int* queue = new int[size + 1];
	int* visited = new int[size + 1];
	int component_num = graph[0][1];
	int* eccentricities = new int[size];
	int* map = new int[size + 1];

	for (int current_component = 0; current_component < component_num; current_component++) {
		int componentSize = components[component_num][current_component];
		if (componentSize == 1) {
			eccentricities[components[current_component][0] - 1] = 0;
			continue;
		}
		if (componentSize == 2) {
			eccentricities[components[current_component][0] - 1] = 1;
			eccentricities[components[current_component][1] - 1] = 1;
			continue;
		}
		if (componentSize == size) {
			printEccentricityOfVertices_l(graph, size);
			return;
		}
		int* distances = new int[componentSize+1];
		memset(map, 0, (size + 1) * sizeof(int));
		//printf("Component: %d\n", current_component + 1);
		for (int i = 0; i < componentSize; i++) {
			map[components[current_component][i]] = i+1;
			//printf("%d ", components[current_component][i]);
		}
		//printf("\n");
		//print map
		//for (int i = 1; i <= size; i++) {
		//	//cout << map[i] << " ";
		//	printf("map[%d]: %d ", i, map[i]);
		//}
		//printf("\n");
		for (int h = 0; h < componentSize; h++) {
			int front = 0;
			int back = 0;
			int queued = 0;
			int fists_V = components[current_component][h];
			//clear with memset
			memset(distances, 0, componentSize * sizeof (int) +1);
			memset(visited, 0, (size + 1) * sizeof(int));
			visited[fists_V] = true;
			queue[back++] = fists_V;
			queued++;
			int maxDistance = 0;
			while (back != front) {
				int u = queue[front++];
				//printf("visiting: %d\n", u);
				
				for (int i = 1; i <= graph[u][0]; i++) {
					int v = graph[u][i];
					if (!visited[v]) {
						visited[v] = true;
						distances[map[v]] = distances[map[u]] + 1;
						
						//printf("queued: %d\n", v);
						//printf("distance to %d: %d\n", v, distances[map[v]]);
						//printf("distance[%d]: %d\n", map[v], distances[map[v]]);
						queue[back++] = v;
						queued++;
					}
					if (queued == componentSize) {
						//printf("break\n");

						maxDistance = distances[map[v]];
						back = front;
						break;
					}

				}
				
			}
			//maxDistance = *max_element(distances + 1, distances + size + 1);
			eccentricities[components[current_component][h]-1] = maxDistance;
			//cout << eccentricity << " ";
		}
		delete[] distances;
	}
	for (int i = 0; i < size; i++) {
		//cout << eccentricities[i] << " ";
		printf("%d ", eccentricities[i]);
	}
	delete[] eccentricities;
	delete[] queue;
	delete[] visited;
	//cout << endl;
	printf("\n");
	delete[] map;
}
void printEccentricityOfVertices_l(int** graph, int size) {

	int* queue = new int[size + 1];
	int* distances = new int[size + 1];
	int* visited = new int[size + 1];
	int* component = new int[size + 1];

	for (int j = 1; j <= size; ++j) {
		int front = 0;
		int back = 0;
		int queued = 0;
		//clear with memset
		memset(distances, 0, (size + 1) * sizeof(int));
		memset(visited, 0, (size + 1) * sizeof(int));
		/*for (int i = 1; i <= size; ++i) {
			distances[i] = 0;
			visited[i] = false;
		}*/
		visited[j] = true;
		queue[back++] = j;
		queued++;
		int maxDistance = 0;
		while (back != front) {
			int u = queue[front++];
			if (queued == size) {
				break;
			}
			for (int i = 1; i <= graph[u][0]; ++i) {
				int v = graph[u][i];
				if (!visited[v]) {
					visited[v] = true;
					distances[v] = distances[u] + 1;
					queue[back++] = v;
					queued++;
				}
				if (queued == size) {
					maxDistance = distances[v];
					back = front;
					break;
				}
			}

		}
		//cout << eccentricity << " ";
		printf("%d ", maxDistance);
	}

	delete[] queue;
	delete[] distances;
	delete[] visited;
	delete[] component;
	//cout << endl;
	printf("\n");

}

//5
void printIsPlanar_l(int** graph, int n) {
	//check number of edges and vertices
	int edges = 0;
	int vertices = n;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (graph[i][j] == 1) {
				edges++;
			}
		}
	}
	if (edges > 3 * vertices - 6) {
		cout << "F" << endl;
	}
	else {
		if (isSubgraphHomeomorphicToK5_l(vertices, graph)) {
			cout << "F" << endl;
		}
		else if (isSubgraphHomeomorphicToK33_l(vertices, graph)) {
			cout << "F" << endl;
		}
		else
			cout << "T" << endl;
	}
}

bool isSubgraphHomeomorphicToK5_l(int n, int** graph)
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

bool isSubgraphHomeomorphicToK33_l(int n, int** graph)
{
	return false;
}


int findMinAvailablecolour(bool* availablecolours, int numcolours) {
	for (int colour = 1; colour <= numcolours; ++colour) {
		if (availablecolours[colour]) {
			return colour;
		}
	}
	return numcolours + 1; // In case all colours are taken, assign a new colour
}

//6a
void printVerticesColours_Greedy_l(int** graph, int size) {
	int* colours = new int[size + 1];
	memset(colours, 0, (size + 1) * sizeof(int));


	for (int u = 1; u <= size; ++u) {
		BalancingTree unavailable_colours;
		for (int i = 1; i <= graph[u][0]; ++i) {
			int v = graph[u][i];
			if (colours[v] != 0) {
				unavailable_colours.insert(colours[v]);
			}
		}
		int colour = 1;
		while (unavailable_colours.find(colour)) {
			colour++;
		}

		colours[u] = colour;

		//std::cout << colours[u] << " " ;
		
	}
	for (int i = 1; i <= size; i++) {
		//cout << colours[i] << " ";
		printf("%d ", colours[i]);
	}
	//std::cout << std::endl;
	printf("\n");
	// Free allocated memory
	delete[] colours;
	//delete[] availablecolours;
}

//6b

void sortVerticesByDegree(int**graph, int* vertices, int size) {
	/*for (int i = 1; i < size; i++) {
		for (int j = i + 1; j <= size; j++) {
			if (degrees[vertices[i]] < degrees[vertices[j]]) {
				std::swap(vertices[i], vertices[j]);
				
			}
			else if (degrees[vertices[i]] == degrees[vertices[j]]) {
				if (vertices[i] > vertices[j]) {
					std::swap(vertices[i], vertices[j]);
				}
			}
		}
	}*/
	my_pair* vert = new my_pair[size];
	for (int i = 0; i < size; i++) {
		vert[i].vertex = vertices[i+1];
		vert[i].degree = graph[vertices[i+1]][0];
	}
	qsort(vert, size, sizeof(my_pair), compare_vertices_by_degree);
	//debug print vertices with degrees
	for (int i = 0; i < size; i++) {
		vertices[i+1] = vert[i].vertex;

	}
	//for (int i = 0; i < size; i++) {
	//cout <<"Vertex: "<< vertices[i] << " Degree: " << degrees[vertices[i]] << endl;
	//}
	delete[] vert;
}

void printVerticesColours_LF_l(int** graph, int size) {
	int* vertices = new int[size + 1];
	int* colours = new int[size + 1];

	for (int i = 0; i <= size; i++) {
		vertices[i] = i;
	}
	memset(colours, 0, (size + 1) * sizeof(int));
	sortVerticesByDegree(graph, vertices, size);


	/*for (int i = 0; i < size; i++) {
		cout << "Vertex: " << vertices[i] << " Degree: " << degrees[vertices[i]] << endl;
	}*/
	// Colour the vertices in order using the greedy algorithm
	for (int u = 1; u <= size; ++u) {
		BalancingTree unavailable_colours;
		int current = vertices[u];

		for (int i = 1; i <= graph[current][0]; ++i) {
			int v = graph[current][i];
			if (colours[v] != 0) {
				unavailable_colours.insert(colours[v]);
			}
		}
		int colour = 1;
		while (unavailable_colours.find(colour)) {
			colour++;
		}
		colours[current] = colour;
	} 

	for (int i = 1; i <= size; ++i) {
		//cout << colours[i] << " ";
		printf("%d ", colours[i]);
	}
	//cout << endl;
	printf("\n");

	// Free the allocated memory
	//delete[] availablecolours;
	delete[] vertices;
	delete[] colours;
}

//6c
int findMaxSaturationVertex(int** graph, int* saturation, bool* coloured, int size, int** components, int current_component, int num_components) {
	int maxSaturation = -1, maxDegree = -1, vertex = -1;
	for (int j = 0; j < components[num_components][current_component]; j++) {
		int i = components[current_component][j];
		if (!coloured[i] && (saturation[i] > maxSaturation || (saturation[i] == maxSaturation && graph[i][0] > maxDegree) || (saturation[i] == maxSaturation && graph[i][0] == maxDegree && i < vertex))) {
			maxSaturation = saturation[i];
			maxDegree = graph[i][0];
			vertex = i;
		}
		
	}
	return vertex;
}

void updateSaturation(int** graph, int* saturation, int vertex, int* colour, int size, int used_colours) {

	for (int i = 1; i <= graph[vertex][0]; i++) {
		int neighbor = graph[vertex][i];
		if (colour[neighbor] == -1) {
			int* neighborscolour = new int[used_colours+1];
			memset(neighborscolour, 0, (used_colours + 1) * sizeof(int));
			for (int j = 1; j <= graph[neighbor][0]; ++j) {
				int adj = graph[neighbor][j];
				if (colour[adj] != -1) {
					neighborscolour[colour[adj]] = true;
				}
			}
			saturation[neighbor] = 0;
			for (int j = 0; j <= used_colours; ++j) {
				if (neighborscolour[j]) {
					saturation[neighbor]++;
				}
			}
			delete[] neighborscolour;
		}
	}
}

void printVerticesColours_SLF_l(int** graph, int size, int** components) {
	int* colour = new int[size + 1];
	int* saturation = new int[size + 1];
	bool* coloured = new bool[size + 1];

	int component_num = graph[0][1];
	memset(colour, -1, (size + 1) * sizeof(int));
	memset(saturation, 0, (size + 1) * sizeof(int));
	memset(coloured, 0, (size + 1) * sizeof(bool));


	//bool* available = new bool[size + 1];
	for (int h = 0; h < component_num; h++) {
		int used_colours = 0;
		for (int i = 1; i <= components[component_num][h]; ++i) {
			int vertex = findMaxSaturationVertex(graph, saturation, coloured, size, components, h, component_num);
			BalancingTree unavailablecolours;

			//memset(available, 1, (size + 1) * sizeof(bool));

			// Mark colours of adjacent vertices as unavailable
			for (int j = 1; j <= graph[vertex][0]; ++j) {
				int neighbor = graph[vertex][j];
				if (colour[neighbor] != -1) {
					unavailablecolours.insert(colour[neighbor]);
				}
			}
			// Find the first available colour
			int c = 1;
			while (unavailablecolours.find(c)) {
				c++;
			}
			colour[vertex] = c;
			coloured[vertex] = true;
			used_colours = used_colours>c?used_colours:c;
			// Update saturation of the neighbours
			updateSaturation(graph, saturation, vertex, colour, size, used_colours);

		}
	}

	// Print the colours assigned to vertices
	for (int i = 1; i <= size; ++i) {
		//cout << colour[i] << " ";
		printf("%d ", colour[i]);
	}
	//cout << endl;
	printf("\n");
	// Free the allocated memory
	//delete[] available;
	delete[] colour;
	delete[] saturation;
	delete[] coloured;
}
//7
void printNumOfC4Subgraphs_l(int** graph, int size, int** components) {
	unsigned long long count = 0;
	int component_num = graph[0][1];
	if (component_num > size - 4)
	{
		printf("0\n");
		return;
	}

	for (int current_component = 0; current_component < component_num; current_component++) {
		int componentSize = components[component_num][current_component];
		if (componentSize < 4) continue;
		int* v1neighbours;
		int* v2neighbours;
		int* v3neighbours;
		int* v4neighbours;
		for (int h = 0; h < componentSize; h++) {
			int v1 = components[current_component][h];
			v1neighbours = graph[v1];
			for (int i = 1; i <= v1neighbours[0]; ++i) {
				int v2 = v1neighbours[i];
				v2neighbours = graph[v2];
				for (int j = 1; j <= v2neighbours[0]; ++j) {
					if (v2neighbours[j] == v1) continue;
					int v3 = v2neighbours[j];
					v3neighbours = graph[v3];
					if (v3 != v1) {
						for (int k = 1; k <= v3neighbours[0]; ++k) {
							if (v3neighbours[k] == v2) continue;
							int v4 = v3neighbours[k];
							v4neighbours = graph[v4];
							if (v4 != v2 && v4 != v1) {
								for (int l = 1; l <= v4neighbours[0]; ++l) {
									if (v4neighbours[l] == v1) {
										count++;
									}
								}
							}
						}
					}
				}
			}
		}
	}

	printf("%llu\n", (count / 8));
	//cout << count/8 << endl;
}
struct StackVertex {
	int v;
	int prev;
	int depth;	
};
void c4dfs_util(int** graph, int size, long long &count) {
	StackVertex* stack = new StackVertex[(size+1)*4];
	int sp = 0;
	for (int i = 1; i <= size; i++) {
		sp = 0;
        stack[sp++] = {i, -1, 0};
        while (sp > 0) {
           StackVertex& u = stack[--sp];
            
			for(int j=1; j<= graph[u.v][0]; j++) {
				int v = graph[u.v][j];

				if (u.depth == 3 && v==i) {
					count++;
					continue;
				}
                else if (u.depth!=3 && u.prev != v) {
                    stack[sp++] = {v, u.v, u.depth + 1};
                }
            }
        }
    }
    delete[] stack;
    count /= 8;
}
void printNumOfC4Subgraphs_optimized(int** graph, int size) {
	long long count = 0;
	c4dfs_util(graph, size, count);
	printf("%lld\n", count);

}
//8
void printNumOfGraphComplementsEdges_l(int** graph, int size) {
	unsigned long long maxEdges = (unsigned long long)(((unsigned long long)size * (unsigned long long)(size-1)) / 2);
	unsigned long long edges = 0;
	for (int i = 1; i <= size; i++) {
		edges += graph[i][0];
	}
	
	printf("%llu\n", (maxEdges - (edges/2)));
	//cout << maxEdges-(edges/2) << endl;

}