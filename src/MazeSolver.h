#ifndef MAZESOLVER
#define MAZESOLVER
#include "Graph.h"
#include "Solution.h"
void dijkstraSolve(Graph g,Stack* solution);
int visitNode(Graph graph, int node, int end, int *visited, Stack *stack);
void solve(Graph graph, int start, int end, int *visited, Stack *stack);
int getEdge(Graph g, int n,int m);
#endif
