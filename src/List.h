#ifndef _LIST_H_
#define _LIST_H_
#include <stdio.h>
typedef struct elem{
int i;
struct elem* nxt;
}*List;
List addToList(List l,int i);
List removeFromList(List l,int i);
List getListElem(List l ,int i);
void freeList(List l);
void printList(List l);
#endif
