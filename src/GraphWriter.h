#ifndef GRAPH_WRITER
#define GRAPH_WRITER
#include "Graph.h"

void printVertToStream(FILE * stream,Graph g);
int* readVertFromStream(FILE* file,int n);
int readGraphFromFile(FILE *plik, Graph graph);
int startVert(FILE *plik);
int endVert(FILE *plik);


#endif
