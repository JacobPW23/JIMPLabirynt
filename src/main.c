#include "Solution.h"
#include "MazeSolver.h"
#include "ShowSolution.h"
#include "GraphReader.h"
#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include <unistd.h>
#define HELP_PRINT() \
	printf("Rozwiązywanie labiryntu w formacie grafu\n");\
	printf("Opcje:\n");\
	printf("s - plik grafu opisującego labirynt\n");\
	printf("h - pomoc\n");\
	printf("a - algorytm: dfs, dijkstra, domyślnie - A*\n");\


int main(int argc,char** argv){
	int c;
	void (*solveFunction)(Graph g,Path* s)=astarSolve;
	char* graph_file=NULL;
	if(argc<2){
		HELP_PRINT();
	}
	while((c=getopt(argc,argv,"hs:a:"))!=-1){


		switch(c){

			case 'h':{
					 HELP_PRINT();
					 break;
				 }
			case 's':
				 {

					 graph_file=optarg;
					 break;


				 }
			case 'a':{
					 if(!strcmp(optarg,"dfs"))
						 solveFunction=solve;
					 else if(!strcmp(optarg,"dijkstra"))
						 solveFunction=dijkstraSolve;

				 } 


		}


	}
	if(graph_file!=NULL){
		FILE* plik=fopen(graph_file,"r");
		if(plik==NULL){
			printf("Błąd: Nie udało otworzyć się pliku lub plik nie istnieje\n");
			return 1;
		}
		int n=vertNum(plik);
		Graph gr=createGraph(n);
		if(readGraphFromFile(plik, gr)){
			printf("Błąd: Nie udało wczytać się grafu z pliku\n");
			return 1;
		}
		printf("Wczytano graf\n");
		Path *stack=NULL;
		initPath(&stack);
		(*solveFunction)(gr, stack);
		printSolution(stack, gr);
		freeGraph(gr);
		freePath(stack);
		fclose(plik);
	}
	else
		printf("Podaj nazwe pliku!\n");





	return 0;
}
