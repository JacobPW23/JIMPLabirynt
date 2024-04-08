#ifndef MAZE_READER
#define MAZE_READER 
#include "Graph.h"

int validFile(FILE * file);
int assembleGraph(Graph g,char * filename);
int readRLE8File(char* file_name);

#endif
