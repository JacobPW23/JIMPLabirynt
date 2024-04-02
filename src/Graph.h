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

Graph createGraph(int n);
int assembleGraph(Graph g,char * filename);
int initNeighbourTable(Graph g,int begin,int end);
int establishNeighbourhood(Graph g,int i,int n);
int addVert(Graph g,int x,int y);
void freeGraph(Graph g);
int browseBuforedNumber(List l,Graph g,int x);
void printGraph(Graph g);
#endif
