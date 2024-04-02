#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#define CROSSCODE 184
#define TURNCODE 240
#define DEADENDCODE 296
#define MAX_LINE_SIZE 2052

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

	if((g->neighbors=malloc(10*sizeof (*g->neighbors)))==NULL){
		free(g->cords);
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
			free(g->cords);
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
		free(gr);
		fprintf(stderr, "Nie udało się stworzyć grafu\n");
		return NULL;
	}
	gr->n=n;
	gr->cords=malloc(2*n*sizeof(int));
	gr->neighbours=malloc(n*sizeof(int*));
	if(gr->neighbours==NULL)
	{
		free(gr->neighbours);
		fprintf(stderr, "Nie udało się zaalokować pamięci na sąsiadów\n");
		return NULL;
	}
	for(int i=0;i<n;i++)
	{
		gr->neighbours[i]=malloc(4*sizeof(int));
		if(gr->neighbours[i]==NULL)
		{
			free(gr->neighbours[i]);
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
			free(g->cords);
			free(g);
			fprintf(stderr,"Błąd 2 Zabrakło pamięci na rozwiązanie labiryntu\n");
			return 1;
		}


	}
	for(int i=begin;i<end;i++)
		memset(g->neighbors[i],-1,4*sizeof(int));
	return 0;

}

void printVertToStream(FILE * stream,Graph g){
	for(int i=0;i<g->n;i++){
		fprintf(stream,"%d %d",g->cords[2*i],g->cords[2*i+1]);
		for(int j=0;j<4;j++){
			fprintf(stream," %d", g->neighbors[i][j]);

		}
		if(i==g->start){
			fprintf(stream," %d",1);
		}
		else if(i==g->end)
			fprintf(stream," %d",2);
		else
			fprintf(stream," %d",0);
		fprintf(stream,"\n");
	}
}



int establishNeighborhood(Graph g,int i,int n){
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
 		 free(g->neighbors[i]);
 	}
 	free(g->neighbors);
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
		printf("Neighbors: ");
		for(int j=0;g->neighbors[i][j]!=-1 && j<4;j++){
		printf("%d ",g->neighbors[i][j]);
	
		}
		printf("\n\n");

	}



}

int assembleGraph(Graph g,char * filename){
FILE* file=fopen(filename,"r");
if(file==NULL){
        fprintf(stderr,"Błąd 1 Plik \"%s\" nie istnieje lub nie można go otworzyć\n",filename);
        return 1;
}
int x=1;
char curr [MAX_LINE_SIZE] ;
char prev [MAX_LINE_SIZE];
char nxt [MAX_LINE_SIZE];
List l=NULL;
int tmp=-1;

fgets(prev,MAX_LINE_SIZE,file);
fgets(curr,MAX_LINE_SIZE,file);
fgets(nxt,MAX_LINE_SIZE,file);
do
{

        for(int i=1;i<strlen(curr)-1;i++){
                if(curr[i]==' '){

                        int se=(int)(curr[i-1]+curr[i+1]+prev[i]+nxt[i]);
                        if(se<=CROSSCODE ){
                                addVert(g,i,x);
                                if(curr[i-1]==' ')
                                        establishNeighbourhood(g,g->n-2,g->n-1);
                                if((tmp=browseBuforedNumber(l,g,i))!=-1){

                                        establishNeighbourhood(g,g->n-1,tmp);
                                        l=removeFromList(l,tmp);

                                }
                                if(nxt[i]==' '){
                                        if((l=addToList(l,g->n-1))==NULL){

                                                return 1;
                                        }
                                }
                        }
                        else if(se==DEADENDCODE){
                        addVert(g,i,x);
                        if(prev[i]==' '){
                                if((tmp=browseBuforedNumber(l,g,i))!=-1){

                                        establishNeighbourhood(g,g->n-1,tmp);
                                        l=removeFromList(l,tmp);

                                }

                        }
                        else if(curr[i-1]==' '){

                                establishNeighbourhood(g,g->n-2,g->n-1);
                        }
                        else if(nxt[i]==' '){
                                if((l=addToList(l,g->n-1))==NULL){
                                        return 1;
                                }

                        }
                        }
                        else if(prev[i]!=nxt[i]&&curr[i-1]!=curr[i+1]&& se==TURNCODE)
                        {
                                if(nxt[i]==' '){

                                        if(curr[i+1]==' '){

                                                addVert(g,i,x);
                                                if((l=addToList(l,g->n-1))==NULL){
                                                        return 1;
                                                }

                                        }
                                        else{
                                                addVert(g,i,x);
                                                establishNeighbourhood( g,g->n-2,g->n-1);
                                                if((l=addToList(l,g->n-1))==NULL){
                                                        return 1;
                                                }
                                        }
                                }
                                else{

                                        if(prev[i]==' '){
                                                addVert(g,i,x);
                                                if((tmp=browseBuforedNumber(l,g,i))!=-1){

                                                        establishNeighbourhood(g,g->n-1,tmp);
                                                        l=removeFromList(l,tmp);

                                                }
                                        if(curr[i-1]==' ')
                                                establishNeighbourhood( g,g->n-2,g->n-1);
                                        }
                                        }
                        }
                        else if((curr[i-1]=='P' || curr[i+1]=='K')){

                                if(curr[i-1]=='P'){

                                        addVert(g,i,x);
                                        g->start=g->n-1;
                                        if(nxt[i]==' '){
                                                if((l=addToList(l,g->n-1))==NULL)
                                                        return 1;

                                        }
                                }
                                else{
                                        addVert(g,i,x);
                                        g->end=g->n-1;
                                        if(curr[i-1]==' '){
                                                establishNeighbourhood( g,g->n-2,g->n-1);
                                                if(prev[i]==' '){
                                                int tmp;
                                                if((tmp=browseBuforedNumber(l,g,i))!=-1){

                                                        establishNeighbourhood(g,g->n-1,tmp);
                                                        l=removeFromList(l,tmp);

                                                }

                                                }
                                        }
                                        else{
                                                int tmp;
                                                if((tmp=browseBuforedNumber(l,g,i))!=-1){

                                                        establishNeighbourhood(g,g->n-1,tmp);
                                                        l=removeFromList(l,tmp);

                                                }
                                        }


                                }
                        }

                }
        }

        strcpy(prev,curr);
        strcpy(curr,nxt);x++;
}
while(fgets(nxt,MAX_LINE_SIZE,file)!=NULL);
fclose(file);
freeList(l);
return 0;

}

