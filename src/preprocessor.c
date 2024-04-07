#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "MazeReader.h"
#include "GraphWriter.h"
#include "Graph.h"
int main(int argc,char** argv)
{
	
	if(argc>2)
        {
        	char txt[5]=".txt";
        	char maze_file_txt[50]="";
        	char *nazwa=argv[1];
        	char *format=argv[2];
        	strcat(maze_file_txt, nazwa);
        	strcat(maze_file_txt, txt);
        	readRLE8File(nazwa);
        	FILE* out=fopen(format,"w");
        	Graph gr;
        	if((gr=initGraph())==NULL){
        	return 1;
        	}
        	if(assembleGraph(gr, maze_file_txt)!=0){
                	fclose(out);
                	freeGraph(gr);
	 		return 1;
        	}

		printGraphToStream(out,gr);

		if(remove(maze_file_txt)!=0)
			printf("Nie udało się usunąć pliku txt\n");
		fclose(out);
		freeGraph(gr);
	}

	else if(argc==2)
	{
		Graph gr;
		if((gr=initGraph())==NULL)
			return 1;
		FILE *plik=fopen("plik.txt", "r");
		if(assembleGraph(gr, argv[1])!=0)
		{
			fclose(plik);
			freeGraph(gr);
			return 1;
		}
		printGraphToStream(plik, gr);
		fclose(plik);
		freeGraph(gr);
	}
	

	else
	{
		printf("Niepoprawna liczba argumentów\n");
		return 2;	
	}

	return 0;
}
