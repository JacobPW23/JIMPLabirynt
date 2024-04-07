#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#define MAX_LINE_SIZE 2050

Graph initGraph(void){
	Graph g;
	if((g=malloc(sizeof *g))==NULL){
			fprintf(stderr,"Błąd 2 Zabrakło pamięci na rozwiązanie labiryntu\n");
		return NULL;

	}
	if((g->coords=malloc(20*sizeof (*g->coords)))==NULL){
  		free(g);
		fprintf(stderr,"Błąd 2 Zabrakło pamięci na rozwiązanie labiryntu\n");
  		return NULL;

	}

	if((g->neighbors=malloc(10*sizeof (*g->neighbors)))==NULL){
		free(g->coords);
		free(g);
		fprintf(stderr,"Błąd 2 Zabrakło pamięci na rozwiązanie labiryntu\n");
		return NULL;
	}
	g->n=0;

	for(int i=0;i<10;i++){
		if((g->neighbors[i]=malloc(4*sizeof(int)))==NULL){

			for(int j=i-1;j>=0;j--){

				free(g->neighbors[j]);
			}
			free(g->neighbors);
			free(g->coords);
			free(g);
			fprintf(stderr,"Błąd 2 Zabrakło pamięci na rozwiązanie labiryntu\n");
			return NULL;
		}


	}
	for(int i=0;i<10;i++)
		memset(g->neighbors[i],-1,4*sizeof(int));


	g->size=10;
	g->start=-1;
	g->end=-1;
	return g;
}

Graph createGraph(int n)
{
	Graph gr=malloc(sizeof(*gr));
	if(gr==NULL)
	{
		fprintf(stderr, "Błąd: Nie udało się stworzyć grafu\n");
		return NULL;
	}
	gr->n=n;
	gr->size=n;
	if((gr->coords=malloc(2*n*sizeof*gr->coords))==NULL){
		free(gr);
		fprintf(stderr, "Błąd: Nie udało się zaalokować pamięci na współrzędne\n");

	}
	gr->neighbors=malloc(n*sizeof*gr->neighbors);
	if(gr->neighbors==NULL)
	{
		free(gr->coords);
		free(gr);
		fprintf(stderr, "Nie udało się zaalokować pamięci na sąsiadów\n");
		return NULL;
	}
	for(int i=0;i<n;i++)
	{
		gr->neighbors[i]=malloc(4*sizeof*gr->neighbors[i]);
		if(gr->neighbors[i]==NULL)
		{
			for(int j=i-1;j>=0;j--)
				free(gr->neighbors[j]);
			free(gr->neighbors);
			free(gr->coords);
			free(gr);
			fprintf(stderr, "Nie udało się zaalokować pamięci na sąsiadów wierzchołka\n");
			return NULL;
		}
	}
	
	return gr;	
}

int initNeighborTable(Graph g,int begin,int end){

	for(int i=begin;i<end;i++){
		if((g->neighbors[i]=realloc(g->neighbors[i],4*sizeof(int)))==NULL){

			for(int j=i-1;j>=0;j--){

				free(g->neighbors[j]);
			}
			free(g->neighbors);
			free(g->coords);
			free(g);
			fprintf(stderr,"Błąd 2 Zabrakło pamięci na rozwiązanie labiryntu\n");
			return 1;
		}


	}
for(int i=begin;i<end;i++)
		memset(g->neighbors[i],-1,4*sizeof(int));
	return 0;

}



int establishNeighbourhood(Graph g,int i,int n){
	int j=0;
	if(i>g->n || n>g->n)
		return 1;
	for(j;g->neighbors[i][j]!=-1;j++);
	if(g->neighbors[i][j]!=-1){
		return 1;
	}
	else{

		g->neighbors[i][j]=n;
	}
		for(j=0;g->neighbors[n][j]!=-1;j++);
	if(g->neighbors[n][j]!=-1){
		return 1;
	}
	else{

		g->neighbors[n][j]=i;	
	}	
return 0;

}



int addVert(Graph g,int x,int y){
	if(g->n < g->size){
		g->coords[2*g->n]=x;
		g->coords[2*g->n+1]=y;
		g->n++;
		return 0;
	}
	else{
		if((g->coords=realloc(g->coords,4*g->size*sizeof (*g->coords)))==NULL){
			freeGraph(g);
			fprintf(stderr,"Błąd 2 Zabrakło pamięci na rozwiązanie labiryntu\n");
			return 1;
				}
		if((g->neighbors=realloc(g->neighbors,2*g->size*sizeof (*g->neighbors)))==NULL){
			freeGraph(g);
			fprintf(stderr,"Błąd 2 Zabrakło pamięci na rozwiązanie labiryntu\n");
			return 1;
				}
		if(initNeighborTable(g,g->size,g->size*2)==1){
			freeGraph(g);
			fprintf(stderr,"Błąd 2 Zabrakło pamięci na rozwiązanie labiryntu\n");
			return 1;
		}
		g->size*=2;
		g->coords[2*g->n]=x;
		g->coords[2*g->n+1]=y;
		g->n++;
		return 0;
	}
	return 0;

}


void freeGraph(Graph g){
       free(g->coords);
       for(int i=0;i<g->size;i++){
 		 free(g->neighbors[i]);
 	}
 	free(g->neighbors);
 	free(g);
}



int browseBuforedNumber(List l,Graph g,int x){
	List tmp=l;
	while(tmp!=NULL){
		if(g->coords[2*tmp->i]==x){

			return tmp->i;
		}
		tmp=tmp->nxt;
	
	}
	return -1;

}



void printGraph(Graph g){
	for(int i=0;i<g->n;i++){

		printf("Vertice nr. %d\n",i);
		printf("Cords: %d %d \n",g->coords[2*i],g->coords[(2*i)+1]);
		printf("Neighbors: ");
		for(int j=0;g->neighbors[i][j]!=-1 && j<4;j++){
		printf("%d ",g->neighbors[i][j]);
	
		}
		printf("\n\n");

	}
}

