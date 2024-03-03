#include "Maze.h"
#include <stdio.h>
#include<stdlib.h>
#include "MazeSolver.h"
int main(int argc,char** argv){

	if(argc>1){
		Graph gr;
		if(( gr=initGraph())==NULL){
		return 1;	
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
