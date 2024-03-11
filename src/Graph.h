#ifndef _GRAPH_H
#define _GRAPH_H
#include <stdio.h>
#include "List.h"
typedef struct {
int* cords;
int** neighbors;
int n;
int size;
int start;
int end;
}*Graph;
Graph initGraph();
int assembleGraph(Graph g,char * filename);
void printVertToStream(FILE * stream,Graph g);
int initNeighborTable(Graph g,int begin,int end);
int establishNeighborhood(Graph g,int i,int n);
int addVert(Graph g,int x,int y);
void freeGraph(Graph g);
int browseBuforedNumber(List l,Graph g,int x);
void printGraph(Graph g);
#endif
