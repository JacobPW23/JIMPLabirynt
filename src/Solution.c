#include<stdlib.h>
#include<stdio.h>
#include "MazeSolution.h"

void printSolution(Stack *stack, FILE *plik)
{
	rewind(plik);
	while(stack->top!=NULL && stack->top->next!=NULL)
	{

		int* cords=readCords(plik, stack->top->node);
		int x_curr=cords[0];
		int y_curr=cords[1];
		cords=readCords(plik, stack->top->next->node);
		int x_next=cords[0];
		int y_next=cords[1];

		if(x_curr==x_next)
		{
			if(y_curr>y_next)
			{
				printf("Góra %d\n", y_curr-y_next);
			}
			if(y_curr<y_next)
			{
				printf("Dół %d\n", y_next-y_curr);
			}
		}

		else if(y_curr==y_next)
		{
			if(x_curr>x_next)
			{
				printf("Lewo %d\n", x_curr-x_next);
			}
			if(x_curr<x_next)
			{
				printf("Prawo %d\n", x_next-x_curr);
			}
		}

		else
			printf("Błąd\n");
		stack->top=stack->top->next;
	}
}


