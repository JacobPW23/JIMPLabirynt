#include <stdlib.h>
#include <stdio.h>
#include "MazeSolver.h"
#include "Graph.h"

int initStack(Stack **stack)
{
	*stack=malloc(sizeof(Stack));
	if(*stack==NULL)
	{
		printf("Nie udalo sie zainicjowac stosu\n");
		return 1;
	}
	(*stack)->top=NULL;
	return 0;
}

int push(Stack *stack, int node)
{
    Node *newNode=malloc(sizeof(Node));
    if(newNode==NULL)
    {
    	printf("Nie udalo sie zaalokowac pamieci na wezel\n");
	return 1;
    }
    newNode->node=node;
    newNode->next=stack->top;
    stack->top=newNode;

    return 0;
}

int pop(Stack *stack)
{
    if(stack==NULL || stack->top==NULL)
    {
    	printf("Stos jest pusty\n");
    	return 1;
    }
    
    Node *temp=stack->top;
    stack->top=temp->next;

    free(temp);
    return 0;
}

void reverse(Stack *stack)
{
	if(stack->top!=NULL)
	{
		int temp=stack->top->node;
		pop(stack);
		reverse(stack);

		insertAtBottom(stack, temp);
	}
}

void insertAtBottom(Stack *stack, int node)
{
	if(stack->top==NULL)
		push(stack, node);
	else
	{
		int temp = stack->top->node;
		pop(stack);
        	insertAtBottom(stack, node);
	
        	push(stack, temp);

	}
}

int visitNode(Graph graph, int node, int end, int *visited, Stack *stack)
{
    visited[node]=1;
    push(stack, node);
    for(int i=0;graph->neighbours[node][i]!=-1;i++)
    {
        if(graph->neighbours[node][i]==end)
        {
            printf("Znaleziono ścieżkę\n");
            return 1;
        }
	else if(visited[graph->neighbours[node][i]]==0)
        {
	    if(visitNode(graph, graph->neighbours[node][i], end, visited, stack))
            	return 1;
        }

        
    }
    pop(stack);
    return 0;
}

void solve(Graph graph, int start, int end, int *visited, Stack *stack)
{
    for(int i=0;i<graph->n;i++)
    {
	    visited[i]=0;
    }

    visitNode(graph, start, end, visited, stack);
}

void printStack(Stack *stack)
{
	Node *temp=stack->top;
	while(temp!=NULL)
	{
		printf("%d\n", temp->node);
		temp=temp->next;
	}
}

void freeStack(Stack *stack)
{
	while(stack->top!=NULL)
	{
		Node *temp=stack->top;
		stack->top=stack->top->next;
		free(temp);
	}
}
