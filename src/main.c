#include "Maze.h"
#include "Solution.h"
#include "MazeSolver.h"
#include "ShowSolution.h"
#include "MazeReader.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char** argv){

	if(argc>1)
	{	
		FILE *plik=fopen(argv[1], "r");
		if(plik==NULL)
		{
			printf("Nie udało się otworzyć pliku\n");
			return 1;
		}
		

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
	}
	else
		printf("Podaj nazwe pliku!\n");


	

return 0;
}
