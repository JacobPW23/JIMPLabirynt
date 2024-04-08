#include <stdio.h>
#include <stdlib.h>
#include "Solution.h"

int initPath(Path **stack)
{
        *stack=malloc(sizeof(Path));
        if(*stack==NULL)
        {
                printf("Nie udalo sie zainicjowac stosu\n");
                return 1;
        }
        (*stack)->top=NULL;
        return 0;
}

int push(Path *stack, int node)
{
    PathNode *newPathNode=malloc(sizeof(PathNode));
    if(newPathNode==NULL)
    {
        printf("Nie udalo sie zaalokowac pamieci na wezel\n");
        return 1;
    }
    newPathNode->node=node;
    newPathNode->next=stack->top;
    stack->top=newPathNode;

    return 0;
}

int pop(Path *stack)
{
    if(stack==NULL || stack->top==NULL)
    {
        printf("Stos jest pusty\n");
        return 1;
    }

    PathNode *temp=stack->top;
    stack->top=temp->next;

    free(temp);
    return 0;
}

void reverse(Path *stack)
{
        if(stack->top!=NULL)
        {
                int temp=stack->top->node;
                pop(stack);
                reverse(stack);

                insertAtBottom(stack, temp);
        }
}

void insertAtBottom(Path *stack, int node)
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

void printPath(Path *stack)
{
        PathNode *temp=stack->top;
        while(temp!=NULL)
        {
                printf("%d\n", temp->node);
                temp=temp->next;
        }
}

void freePath(Path *stack)
{
        while(stack->top!=NULL)
        {
                PathNode *temp=stack->top;
                stack->top=stack->top->next;
                free(temp);
        }
	free(stack);
}

