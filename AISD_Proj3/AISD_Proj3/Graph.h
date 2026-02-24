#pragma once

#include <iostream>
#include "utils.h"
#include "tree.h"

using namespace std;
void printDegreeSequence_m(int** graph, int size);
void printNumberOfComponents_m(int** graph, int size);
void printIsBipartite_m(int** graph, int size);
void printEccentricityOfVertices_m(int** graph, int size);
void printIsPlanar_m(int** graph, int size);
bool isSubgraphHomeomorphicToK5_m(int size, int** graph);
bool isSubgraphHomeomorphicToK33_m(int size, int** graph);
void printVerticesColours_Greedy_m(int** graph, int size);
void printVerticesColours_LF_m(int** graph, int size);
void printVerticesColours_SLF_m(int** graph, int size);
void printNumOfC4Subgraphs_m(int** graph, int size);
void printNumOfGraphComplementsEdges_m(int** graph, int size);

void printDegreeSequence_l(int** graph, int size);
void printNumberOfComponents_l(int** graph, int size, int** &components);
void printIsBipartite_l(int** graph, int size);
void printEccentricityOfVertices_l(int** graph, int size);
void printIsPlanar_l(int** graph, int size);
bool isSubgraphHomeomorphicToK5_l(int size, int** graph);
bool isSubgraphHomeomorphicToK33_l(int size, int** graph);
void printVerticesColours_Greedy_l(int** graph, int size);
void printVerticesColours_LF_l(int** graph, int size);
void printVerticesColours_SLF_l(int** graph, int size, int** components);
void printNumOfC4Subgraphs_l(int** graph, int size, int** components);
void printNumOfC4Subgraphs_optimized(int** graph, int size);
void printNumOfGraphComplementsEdges_l(int** graph, int size);
void printEccentricityOfVertices_optimized(int** graph, int size, int** components);
