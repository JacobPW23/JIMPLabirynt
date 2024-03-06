#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"


Graph initGraph(void){
	Graph g;
	if((g=malloc(sizeof *g))==NULL){
			fprintf(stderr,"Błąd 2 Zabrakło pamięci na rozwiązanie labiryntu\n");
		return NULL;

	}
	if((g->cords=malloc(20*sizeof (*g->cords)))==NULL){
  		free(g);
		fprintf(stderr,"Błąd 2 Zabrakło pamięci na rozwiązanie labiryntu\n");
  		return NULL;

	}

	if((g->neighbours=malloc(10*sizeof (*g->neighbours)))==NULL){
		free(g->cords);
		free(g);
		fprintf(stderr,"Błąd 2 Zabrakło pamięci na rozwiązanie labiryntu\n");
		return NULL;
	}
	g->n=0;

	for(int i=0;i<10;i++){
		if((g->neighbours[i]=malloc(4*sizeof(int)))==NULL){

			for(int j=i-1;j>=0;j--){

				free(g->neighbours[j]);
			}
			free(g->neighbours);
			free(g->cords);
			free(g);
			fprintf(stderr,"Błąd 2 Zabrakło pamięci na rozwiązanie labiryntu\n");
			return NULL;
		}


	}
	for(int i=0;i<10;i++)
		memset(g->neighbours[i],-1,4*sizeof(int));


	g->size=10;
	g->start=-1;
	g->end=-1;
	return g;
}


int initNeighbourTable(Graph g,int begin,int end){

	for(int i=begin;i<end;i++){
		if((g->neighbours[i]=realloc(g->neighbours[i],4*sizeof(int)))==NULL){

			for(int j=i-1;j>=0;j--){

				free(g->neighbours[j]);
			}
			free(g->neighbours);
			free(g->cords);
			free(g);
			fprintf(stderr,"Błąd 2 Zabrakło pamięci na rozwiązanie labiryntu\n");
			return 1;
		}


	}
	for(int i=begin;i<end;i++)
		memset(g->neighbours[i],-1,4*sizeof(int));
	return 0;

}



int establishNeighbourhood(Graph g,int i,int n){
	int j=0;
	if(i>g->n || n>g->n)
		return 1;
	for(j;g->neighbours[i][j]!=-1;j++);
	if(g->neighbours[i][j]!=-1){
		return 1;
	}
	else{

		g->neighbours[i][j]=n;
	}
		for(j=0;g->neighbours[n][j]!=-1;j++);
	if(g->neighbours[n][j]!=-1){
		return 1;
	}
	else{

		g->neighbours[n][j]=i;	
	}	
return 0;

}



int addVert(Graph g,int x,int y){
	if(g->n < g->size){
		g->cords[2*g->n]=x;
		g->cords[2*g->n+1]=y;
		g->n++;
		return 0;
	}
	else{
		//we have to increase structure memory
		if((g->cords=realloc(g->cords,4*g->size*sizeof (*g->cords)))==NULL){
			freeGraph(g);
			fprintf(stderr,"Błąd 2 Zabrakło pamięci na rozwiązanie labiryntu\n");
			return 1;
				}
		if((g->neighbours=realloc(g->neighbours,2*g->size*sizeof (*g->neighbours)))==NULL){
			freeGraph(g);
			fprintf(stderr,"Błąd 2 Zabrakło pamięci na rozwiązanie labiryntu\n");
			return 1;
				}
		if(initNeighbourTable(g,g->size,g->size*2)==1){
			freeGraph(g);
			fprintf(stderr,"Błąd 2 Zabrakło pamięci na rozwiązanie labiryntu\n");
			return 1;
		}
		g->size*=2;
		g->cords[2*g->n]=x;
		g->cords[2*g->n+1]=y;
		g->n++;
		return 0;
	}
	return 0;

}


void freeGraph(Graph g){
       free(g->cords);
       for(int i=0;i<g->size;i++){
 		 free(g->neighbours[i]);
 	}
 	free(g->neighbours);
 	free(g);


}



int browseBuforedNumber(List l,Graph g,int x){
	List tmp=l;
	while(tmp!=NULL){
		if(g->cords[2*tmp->i]==x){

			return tmp->i;
		}
		tmp=tmp->nxt;
	
	}
	return -1;

}



void printGraph(Graph g){
	for(int i=0;i<g->n;i++){

		printf("Vertice nr. %d\n",i);
		printf("Cords: %d %d \n",g->cords[2*i],g->cords[(2*i)+1]);
		printf("Neighbours: ");
		for(int j=0;g->neighbours[i][j]!=-1 && j<4;j++){
		printf("%d ",g->neighbours[i][j]);
	
		}
		printf("\n\n");

	}



}
