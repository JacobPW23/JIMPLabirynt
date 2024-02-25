#include "List.h"
#include <stdio.h>
#include<stdlib.h>
int main(int argc,char** argv){
	List l=NULL;
	l=removeFromList(l,5);
	l=addToList(l,4);
	l=addToList(l,5);
	l=addToList(l,15);
	printf("Lista po trzech wpisach:\n");
	printList(l);
	l=removeFromList(l,4);
	printf("Lista po usunięciu jednego wpisu:\n");
	printList(l);
	l=addToList(l,89);
	printf("Lista po dodaniu kolejnego wpisu:\n");
	printList(l);
	List tmp =getListElem(l,5);
	printf("Element o wartości 5: %d\n",tmp->i);
	l=removeFromList(l,15);
	tmp=getListElem(l,13);
	printf("Element o wartości 13: %d\n",tmp!=NULL ? tmp->i:-1);
	freeList(l);
	return 0;
}
