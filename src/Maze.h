#ifndef _MAZE_H
#define _MAZE_H
#include<stdio.h>
#include <stdlib.h>
#include "MazeSolver.h"
int assembleGraph(Graph g,char * filename);
void wypisz(Stack *stack, FILE *plik);
void printVertToStream(FILE * stream,Graph g);
int *readVertFromStream(FILE* file,int n);
int *readCords(FILE *plik, int n);
int validFile(FILE * file);
int startVert(FILE *plik);
int endVert(FILE *plik);
int vertNum(FILE *plik);
#endif
