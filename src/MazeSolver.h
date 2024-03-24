#ifndef MAZESOLVER
#define MAZESOLVER
#include "Graph.h"
#include "Solution.h"

int visitNode(Graph graph, int node, int end, int *visited, Stack *stack);
void solve(Graph graph, int start, int end, int *visited, Stack *stack);

#endif
