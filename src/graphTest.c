#include "Graph.h"
#include <stdio.h>
#include<stdlib.h>
void printCords(Graph g);
void printNeighbourhood(Graph g);
int main(int argc,char** argv){
	List li=NULL;
	Graph g=initGraph();
	printf("Kod dodania wierzchołka: %d\n",addVert(g,10,7));
	printf("Kod dodania wierzchołka: %d\n",addVert(g,0,3));
	li=addToList(li,g->n-1);	
	printf("Kod dodania sąsiada: %d\n",establishNeighbourhood(g,0,1));
	printf("Kod dodania sąsiada: %d\n",establishNeighbourhood(g,10,1));
	printf("Kod dodania sąsiada: %d\n",establishNeighbourhood(g,5,1));
	printf("Wielkość po dodaniu:%d\n",g->n);
	printf("Współrzędne w gafie \n");
	printCords(g);
	printf("Sąsiedzi: \n");
	printNeighbourhood(g);
	printf("Numer wierzchołka zdjęty z listy na podstawie odciętej: %d\n",browseBuforedNumber(li,g,10));
	g->n=10;
	printf("Kod dodania wierzchołka: %d\n",addVert(g,0,57));
	printf("Kod dodania wierzchołka: %d\n",addVert(g,15,3));
	printf("Współrzędne w grafie: \n");
	printCords(g);
	printf("Rozmiar struktury po dodaniu wierzchołka przy maksymalnym domyślnym rozmiarze: %d\n",g->size);
	printGraph(g);	
	freeGraph(g);
	freeList(li);	
return 0;
}
void printCords(Graph g){

	for (int k=0;k<g->n;k++)
		printf("%d %d\n",g->cords[2*k],g->cords[2*k+1]);
}
void printNeighbourhood(Graph g){
	for(int i=0;i<g->size;i++){
		for(int j=0;j<4;j++)
			printf("%d ",g->neighbours[i][j]);
		printf("\n");
	}


}
