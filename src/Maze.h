#ifndef _MAZE_H
#define _MAZE_H
#include<stdio.h>
#include <stdlib.h>
#include "MazeSolver.h"
int assembleGraph(Graph g,char * filename);
void wypisz(Stack *stack, Graph graph);
void printVertToStream(FILE * stream,Graph g);
int* readVertFromStream(FILE* file,int n);
int validFile(FILE * file);
#endif
