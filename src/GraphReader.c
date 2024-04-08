#include <stdlib.h>
#include "GraphReader.h"
#define MAX_LINE_SIZE 2054

int vertNum(FILE *plik)
{
	if(plik==NULL)
	{
		fprintf(stderr, "Nie udało się wczytać ilości wierzchołków\n");
		return -1;
	}
	rewind(plik);
	
	int i=0;
	char buff[MAX_LINE_SIZE];
	while(fgets(buff, MAX_LINE_SIZE, plik)!=NULL)
	{
		i++;
	}
	return i-1;
}

int readGraphFromFile(FILE *plik, Graph graph)
{
	int s, e;
	rewind(plik);
	if(plik==NULL)
	{
		fprintf(stderr, "Strumień to NULL \n");
		return 1;
	}

	if(graph==NULL)
	{
		fprintf(stderr, "Nie udało się wczytać grafu z pamięci\n");
		return 2;
	}

	char buff[MAX_LINE_SIZE];
	fgets(buff, MAX_LINE_SIZE, plik);
	sscanf(buff, "%d %d", &s, &e);
	graph->start=s;
	graph->end=e;
	
	for(int i=0; fgets(buff, 2050, plik)!=NULL; i++)
	{
		if(sscanf(buff, "%d %d %d %d %d %d", &graph->coords[2*i], &graph->coords[2*i+1], &graph->neighbors[i][0],&graph->neighbors[i][1], &graph->neighbors[i][2], &graph->neighbors[i][3])!=6)
		{
			fprintf(stderr, "Nie udało się wczytać wierzchołków z bufora\n");
			return 3;
		}

	}
	return 0;
}
