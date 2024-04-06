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
printf("a - algorytm: dfs, astar, domyślnie - dijkstra\n");\


int main(int argc,char** argv){
	int c;
	void (*solveFunction)(Graph g,Stack* s)=dijkstraSolve;
	char* graph_file=NULL;
	while((c=getopt(argc,argv,"hs:a:"))!=-1)
	{

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
					else if(!strcmp(optarg,"astar"))
						solveFunction=astarSolve;
					
				 } 
			case '?':  HELP_PRINT();break;

			
		}


	}
	if(graph_file!=NULL){
		FILE* plik=fopen(graph_file,"r");
		int n=vertNum(plik);
		Graph gr=createGraph(n);
		printf("Wczytano graf\n");
		if(readGraphFromFile(plik, gr)){
			printf("Nie udało wczytać się grafu z pliku\n");
			return 1;
		}
		
		Stack *stack=NULL;
		initStack(&stack);
		(*solveFunction)(gr, stack);
		printStack(stack);
		wypisz(stack, gr);
		freeGraph(gr);
		freeStack(stack);
		fclose(plik);
	}
	else
		printf("Podaj nazwe pliku!\n");



	

return 0;
}
