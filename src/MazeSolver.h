#ifndef MAZESOLVER
#define MAZESOLVER
#include "Graph.h"

typedef struct Node
{
    int node;
    struct Node *next;
}Node;

typedef struct Stack
{
	Node* top;
}Stack;

Node *createNode(int node);

int initStack(Stack **stack);
int isEmpty(Stack *stack);
int push(Stack *stack, int node);
int pop(Stack *stack);
void reverse(Stack *stack);
void insertAtBottom(Stack *stack, int node); 
int visitNode(FILE *plik, int node, int end, int *visited, Stack *stack);
void solve(FILE *plik, int start, int end, int *visited, Stack *stack);
void printStack(Stack *stack);
void freeStack(Stack *stack);

#endif

