#ifndef MAZESOLVER
#define MAZESOLVER
#include "Graph.h"
#include "Solution.h"
void dijkstraSolve(Graph g,Stack* solution);
int visitNode(Graph graph, int node, int end, int *visited, Stack *stack);
void solve(Graph graph, Stack *stack);
void astarSolve(Graph graph, Stack *solution);
int getEdge(Graph g, int n,int m);
int heuristic(Graph g, int vertex);
#endif
