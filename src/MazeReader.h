#ifndef MAZE_READER
#define MAZE_READER
#include "Graph.h"
#include<stdlib.h>
#include <stdio.h>
int vertNum(FILE *plik);
int readGraphFromFile(FILE *plik, Graph graph);

#endif
