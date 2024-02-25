#include "Maze.h"
#include <stdio.h>
#include<stdlib.h>
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
		freeGraph(gr);
	}

return 0;
}
