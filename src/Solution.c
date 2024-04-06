#include <stdio.h>
#include <stdlib.h>
#include "Solution.h"

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
	free(stack);
}

