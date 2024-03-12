#include "Maze.h"
#include <stdio.h>
#include <stdlib.h>
#include "MazeSolver.h"
#include <unistd.h>

int main(int argc,char** argv){
		if(argc>=2)
		{
		FILE *plik=fopen(argv[1], "r");
		if(plik==NULL)
		{
			fprintf(stderr, "Nie udało się otworzyć pliku");
			return 1;
		}
		
		rewind(plik);
		int *visited = malloc(vertNum(plik)*sizeof(int));	
		Stack *stack=NULL;
		initStack(&stack);
		solve(plik, startVert(plik), endVert(plik), visited, stack);
		reverse(stack);
		printStack(stack);
		wypisz(stack, plik);
		freeStack(stack);
		fclose(plik);
		}

		else
			printf("Podaj nazwe pliku!\n");


	

return 0;
}
