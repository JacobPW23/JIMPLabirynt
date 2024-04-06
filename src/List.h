#ifndef _LIST_H_
#define _LIST_H_
#include <stdio.h>
typedef struct elem{
unsigned int i;
struct elem* nxt;
}*List;
List addToList(List l,unsigned int i);
List removeFromList(List l,unsigned int i);
List getListElem(List l ,unsigned int i);
void freeList(List l);
void printList(List l);
#endif
