#ifndef PRORITYQUEUE_H
#define PRIORITYQUEUE_H
#include <stdio.h>
#include <stdlib.h>
typedef struct elm{
	int i;
	int key;
	struct elm* nxt;

}* PQueue;

PQueue promoteElem(PQueue pq,int i,int keyValue);
PQueue add(PQueue pq,int i,int keyValue);
PQueue popElem(PQueue pq,PQueue popped);
void freePQueue(PQueue pq);
int isGreater(int a, int b);
int isGreaterOrEqual(int a, int b);
#endif
