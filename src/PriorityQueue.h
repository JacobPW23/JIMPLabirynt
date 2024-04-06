#ifndef PRORITYQUEUE_H
#define PRIORITYQUEUE_H
#include <stdio.h>
#include <stdlib.h>
typedef struct elm{
	unsigned int i;
	unsigned int key;
	struct elm* nxt;

}* PQueue;

PQueue promoteElem(PQueue pq,int i,unsigned int keyValue);
PQueue add(PQueue pq,int i,unsigned int keyValue);
PQueue popElem(PQueue pq,PQueue popped);
void freePQueue(PQueue pq);
int isGreater(unsigned int a, unsigned int b);
int isGreaterOrEqual(unsigned int a, unsigned int b);
#endif
