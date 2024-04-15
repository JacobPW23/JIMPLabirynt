#include <stdlib.h>
#include <limits.h>
#include "PriorityQueue.h"

PQueue promoteElem(PQueue pq,int i,unsigned int keyValue){
	PQueue tmp=pq;
	PQueue tmp2=pq;
	if(pq==NULL) return pq;
	if(pq->key>=keyValue){
		while(tmp2->nxt!=NULL && tmp2->nxt->i!=i)
			tmp2=tmp2->nxt;
		PQueue elem=tmp2!=NULL?tmp2->nxt:NULL;
		if(tmp2==NULL || elem==NULL)
			return pq;
		tmp2->nxt=elem->nxt;
		elem->nxt=pq;
		elem->key=keyValue;
		return elem;
	}
	while(tmp->nxt!=NULL && keyValue>=tmp->nxt->key)
		tmp=tmp->nxt;

	while(tmp2->nxt!=NULL && tmp2->nxt->i!=i)
		tmp2=tmp2->nxt;

	PQueue elem=tmp2!=NULL?tmp2->nxt:NULL;
	if(elem==NULL || tmp==NULL )
		return pq;
	tmp2->nxt=elem->nxt;;
	elem->nxt=tmp->nxt;
	tmp->nxt=elem;
	elem->key=keyValue;
	return pq;
}
PQueue add(PQueue pq,int i,unsigned int keyValue){

	PQueue new;
	if((new=malloc(sizeof (*new)))==NULL){
		freePQueue(pq);
		fprintf(stderr,"Błąd: Zabrakło pamięci na rozwiązanie labiryntu\n");
		return NULL;
	}
	new->i=i;
	new->key=keyValue;
	if(pq==NULL || pq->key>keyValue){
		new->nxt=pq;

		return new;

	}
	PQueue e=pq;
	while(e->nxt!=NULL && keyValue>=e->nxt->i){
		e=e->nxt;

	}

	new->nxt=e->nxt;
	e->nxt=new;
	return pq;


}
PQueue popElem(PQueue pq,PQueue poped){
	poped->i=pq->i;
	poped->key=pq->key;
	PQueue tmp=pq;
	pq=pq->nxt;
	free(tmp);
	return pq;
}

void freePQueue(PQueue pq){
	while(pq!=NULL){
		PQueue tmp=pq;
		pq=pq->nxt;
		free(tmp);
	}
}

