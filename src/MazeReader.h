#ifndef MAZE_READER
#define MAZE_READER
#include "Graph.h"
#include "List.h"
#include <string.h>
int validFile(FILE * file);
int assembleGraph(Graph g,char * filename);

#endif
