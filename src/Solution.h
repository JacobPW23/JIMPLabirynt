#ifndef MAZE_SOLUTION
#define MAZE_SOLUTION

typedef struct PathNode{

	int node;
	struct PathNode *next;
}PathNode;

typedef struct Path{

	PathNode* top;
}Path;

PathNode *createPathNode(int node);
int initPath(Path **stack);
int isEmpty(Path *stack);
int push(Path *stack, int node);
int pop(Path *stack);
void reverse(Path *stack);
void insertAtBottom(Path *stack, int node);
void printPath(Path *stack);
void freePath(Path *stack);

#endif
