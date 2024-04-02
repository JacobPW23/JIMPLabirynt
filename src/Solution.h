#ifndef MAZE_SOLUTION
#define MAZE_SOLUTION

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
void printStack(Stack *stack);
void freeStack(Stack *stack);

#endif
