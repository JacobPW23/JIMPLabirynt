#ifndef _MAZE_H
#define _MAZE_H
#include<stdio.h>
#include <stdlib.h>
#include "MazeSolver.h"
int assembleGraph(Graph g,char * filename);
void printVertToStream(FILE * stream,Graph g);
int* readVertFromStream(char * filename,int n);
#endif
