#include "Solution.h"
#include "MazeSolver.h"
#include "ShowSolution.h"
#include "MazeReader.h"
#include <stdio.h>
#include<stdlib.h>
#include <unistd.h>
int main(int argc,char** argv){
	int c;
	char* graph_file=NULL;
	while((c=getopt(argc,argv,"hs:"))!=-1)
	{

		switch(c){

			case 'h':{
					printf("Rozwiązywanie labiryntu w formacie grafu\n");
					printf("Opcje:\n");
					printf("s - plik grafu opisującego labirynt\n");
					printf("h - pomoc\n");
					break;
				 }
			case 's':
				 {

					graph_file=optarg;
					break;
					

				 }
			default: c='h'; break;

			
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
		int *visited = malloc(gr->n*sizeof(int));
		
		Stack *stack=NULL;
		initStack(&stack);
		solve(gr, gr->start, gr->end, visited, stack);
		reverse(stack);
		printStack(stack);
		wypisz(stack, gr);
		freeGraph(gr);
		freeStack(stack);
		fclose(plik);
		free(visited);
	}
	else
		printf("Podaj nazwe pliku!\n");



	

return 0;
}
