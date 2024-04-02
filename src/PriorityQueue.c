#include <stdlib.h>
#include "PriorityQueue.h"

PQueue promoteElem(PQueue pq,int i,int keyValue){
	PQueue tmp=pq;
	PQueue tmp2=pq;
	if((isGreaterOrEqual(pq->key,keyValue))){
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
	while(tmp->nxt!=NULL && isGreaterOrEqual(keyValue,tmp->nxt->key))
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
PQueue add(PQueue pq,int i,int keyValue){

		PQueue new;
		if((new=malloc(sizeof (*new)))==NULL){
			freePQueue(pq);
			fprintf(stderr,"Błąd 1 Zabrakło pamięci na rozwiązanie labiryntu\n");
			return NULL;
		}
		new->i=i;
		new->key=keyValue;
	if(pq==NULL){
		new->nxt=NULL;
		pq=new;
		return pq;

	}
	new->nxt=pq;
	return new;

		
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

int isGreater(int a, int b){
	//return 1 when a is greater than b and 0 in another case
	//Value -1 means infinity
	

	return a==-1? 1 : b==-1?0 : a>b;



}
int isGreaterOrEqual(int a, int b){
	//return 1 when a is greater than b and 0 in another case
	//Value -1 means infinity
	
	return a==-1? 1 : b==-1?0 : a>=b;




}

