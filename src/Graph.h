#ifndef _GRAPH_H
#define _GRAPH_H
#include <stdio.h>
#include "List.h"
typedef struct {
int* cords;
int** neighbours;
int n;
int size;
}*Graph;
Graph initGraph();
int initNeighbourTable(Graph g,int begin,int end);
int establishNeighbourhood(Graph g,int i,int n);
int addVert(Graph g,int x,int y);
void freeGraph(Graph g);
int browseBuforedNumber(List l,Graph g,int x);
void printGraph(Graph g);
#endif
