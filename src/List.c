#include "List.h"
#include <stdlib.h>
#include <stdio.h>
List addToList(List l,int i){
	if(l==NULL){

		List new;
		if((new=malloc(sizeof (*new)))==NULL){
			freeList(l);
			fprintf(stderr,"Błąd 2 Zabrakło pamięci na rozwiązanie labiryntu\n");
			return NULL;
		}
		new->i=i;
		new->nxt=NULL;
		l=new;
		return l;

	}
	if(l->nxt==NULL){


	
	List new;
	if((new=malloc(sizeof (*new)))==NULL){
		freeList(l);
		fprintf(stderr,"Błąd 2 Zabrakło pamięci na rozwiązanie labiryntu\n");
		return NULL;
	}
	new->i=i;
	new->nxt=NULL;
	l->nxt=new;
	return l;
	}
	 l->nxt=addToList(l->nxt,i);	
 	return l;	 
}


List removeFromList(List l,int i){
	List e=l;
	if(l!=NULL && l->i==i){
		List exterminated=l;
		l=l->nxt;
		free(exterminated);
		return l;

	}
	while(e!=NULL ){
		if(e->nxt->i==i){

			List exterminated=e->nxt;
			e->nxt=e->nxt->nxt;
			free(exterminated);return l;
		}

	e=e->nxt;
	}
return l;
}


List getListElem(List l,int i){

List e=l;
while(e!=NULL && e->i!=i){
e=e->nxt;

}
return e;

}
void freeList(List l){
List tmp;
while(l!=NULL){
tmp=l;
l=l->nxt;
free(tmp);
}
}
void printList(List l){
int i=0;
while(l!=NULL){
printf("Element numer %d : %d\n",i++,l->i);
l=l->nxt;
}

}
