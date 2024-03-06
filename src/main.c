#include "Maze.h"
#include <stdio.h>
#include<stdlib.h>
#include "MazeSolver.h"
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

			
		}
	}	

		if(graph_file!=NULL){
                FILE* out=fopen(graph_file,"w");
                if(out==NULL){
                fprintf(stderr,"Błąd 1 Nie udało się otworzyć pliku lub plik nie istnieje.\n");

                }
                fclose(out);
        	}	

		if(assembleGraph(gr,argv[1])!=0){
			return 1;
		}
		printGraph(gr);
		printf("\nGraph's memory alocated: %ld B \n",gr->size*6*sizeof(int));
		printf("Graph's memory usage: %ld B\n",gr->n*6*sizeof(int));
		int *visited = malloc(100*sizeof(int));
		
		Stack *stack=NULL;
		initStack(&stack);
		solve(gr, 0, 77, visited, stack);
		reverse(stack);
		printStack(stack);
		wypisz(stack, gr);
		freeGraph(gr);
		freeStack(stack);
	}
	else
		printf("Podaj nazwe pliku!\n");


	

return 0;
}
