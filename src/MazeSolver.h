#ifndef MAZESOLVER
#define MAZESOLVER
#include "Graph.h"
#include "Solution.h"
void dijkstraSolve(Graph g,Path* solution);
int visitNode(Graph graph, int node, int end, char* visited, Path* stack);
void solve(Graph graph, Path *stack);
void astarSolve(Graph graph, Path *solution);
int heuristic(Graph g, int vertex);
#endif
