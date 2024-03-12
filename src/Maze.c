#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Maze.h"
#define MAX_LINE_SIZE 2050
#define CROSSCODE 184
#define TURNCODE 240
#define DEADENDCODE 296

int assembleGraph(Graph g,char * filename){
FILE* file=fopen(filename,"r");
if(file==NULL){

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
		if(curr[i]==32){

		 	int se=(int)(curr[i-1]+curr[i+1]+prev[i]+nxt[i]);
			if(se<=184 ){
				addVert(g,i,x);
				if(curr[i-1]==' ')
					establishNeighbourhood(g,g->n-2,g->n-1);
				if((tmp=browseBuforedNumber(l,g,i))!=-1){



					establishNeighbourhood(g,g->n-1,tmp);
					l=removeFromList(l,tmp);

				}	
				if(nxt[i]==' '){
					l=addToList(l,g->n-1);	
				}
			}
			else if(se==296){
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
				l=addToList(l,g->n-1);

			}
			}
			else if(prev[i]!=nxt[i]&&curr[i-1]!=curr[i+1]&& se==240)
			{
				if(nxt[i]==' '){

					if(curr[i+1]==' '){

						addVert(g,i,x);
						l=addToList(l,g->n-1);
						
					}
					else{
						addVert(g,i,x);
						establishNeighbourhood( g,g->n-2,g->n-1);
						l=addToList(l,g->n-1);
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
					if(nxt[i]==' ')
						l=addToList(l,g->n-1);
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


void wypisz(Stack *stack, FILE *plik)
{
	rewind(plik);
	while(stack->top!=NULL && stack->top->next!=NULL)
	{

		int *cords=readCords(plik, stack->top->node);
		int x_curr=cords[0];
		int y_curr=cords[1];
		cords=readCords(plik, stack->top->next->node);
		int x_next=cords[0];
		int y_next=cords[1];

		if(x_curr==x_next)
		{
			if(y_curr>y_next)
			{
				printf("Góra %d\n", y_curr-y_next);
			}
			if(y_curr<y_next)
			{
				printf("Dół %d\n", y_next-y_curr);
			}
		}

		else if(y_curr==y_next)
		{
			if(x_curr>x_next)
			{
				printf("Lewo %d\n", x_curr-x_next);
			}
			if(x_curr<x_next)
			{
				printf("Prawo %d\n", x_next-x_curr);
			}
		}

		else
			printf("Błąd\n");
		stack->top=stack->top->next;
	}
}

void printVertToStream(FILE * stream,Graph g){

	rewind(stream);
	for(int i=0;i<g->n;i++){
		fprintf(stream,"%d %d",g->cords[2*i],g->cords[2*i+1]);
		for(int j=0;j<4;j++){
			fprintf(stream," %d", g->neighbours[i][j]);

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
	rewind(stream);
}



int* readVertFromStream(FILE *stream, int n) {
    rewind(stream);
    if (stream == NULL) {
        return NULL;
    }
    
    char tmp[100];
    int* vert = malloc(5 * sizeof(*vert));
    if (vert == NULL) {
        fprintf(stderr, "Zabrakło pamięci na dalsze procedowanie rozwiązania\n");
        return NULL;
    }

    for (int i = 0; i < 5; i++) {
        vert[i] = -1;
    }

    int dummy, line = 0;
    while (line <= n && fgets(tmp, sizeof(tmp), stream) != NULL) {
        if (line == n) {
            if(sscanf(tmp, "%d %d %d %d %d %d %d", &dummy, &dummy, vert, vert + 1, vert + 2, vert + 3, &dummy)<5){
               free(vert);
               fprintf(stderr, "Niepoprawna liczba elementów w linii %d w pliku\n", n);
               return NULL;
           }
        }
        line++;

    }
    rewind(stream);
    return vert;

}

int *readCords(FILE *plik, int n)
{
	rewind(plik);
	if(plik==NULL)
	{
		fprintf(stderr, "Plik to NULL\n");
		return NULL;
	}
	char buff[100];
	int *cords=malloc(2*sizeof(int));
	for(int i=0;i<=n;i++)
	{
		fgets(buff, 100, plik);
	}
	if(sscanf(buff, "%d %d", cords, cords+1)<2)
	{
		fprintf(stderr, "Nie udało się wczytać współrzędnych\n");
		return NULL;
	}

	return cords;
}

int validFile(FILE * file){
	char buff [MAX_LINE_SIZE];int x=1;
	fgets(buff,MAX_LINE_SIZE,file);
	int l= strlen(buff);
	do
	{
		if(strlen(buff)!=l){
			fprintf(stderr,"Błąd 2 Nieprawidłowy format pliku. Liczby znaków w liniach %d i %d nie są równe.\n",x-1,x);	
			return 1;

		}
		for(int i=0;i<strlen(buff)-1;i++){

			if(buff[i]!=' ' && buff[i]!='X' && buff[i]!='P' && buff[i]!='K')
			{
				fprintf(stderr,"Błąd 0 Nieznany znak \'%c\' w linii %d, kolumna %d.\n",buff[i],x,i);
				return 2; 
	
			}

		}
		x++;
		
	}
	while(fgets(buff,MAX_LINE_SIZE,file)!=NULL);
	rewind(file);
	return 0;
}

int startVert(FILE *plik)
{
	if(plik==NULL)
	{
		fprintf(stderr, "Plik to NULL\n");
		return -1;
	}
	rewind(plik);
	int dummy;
	int start;
	int i=0;
	while(fscanf(plik, "%d %d %d %d %d %d %d", &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &start)==7)
	{
		if(start==1)
		{	
			rewind(plik);
			return i;
		}
		i++;
	}
        rewind(plik);
	return -2;
}

int endVert(FILE *plik)
{
	if(plik==NULL)
	{
		fprintf(stderr, "Plik to NULL\n");
		return -1; 
	}
	rewind(plik);
	int dummy;
	int end; 
	int i=0;
	while(fscanf(plik, "%d %d %d %d %d %d %d", &dummy, &dummy, &dummy, &dummy, &dummy, &dummy, &end)==7)
	{				                      
		if(end==2)
		{
    			rewind(plik);			
			return i;
		}
		i++;
	}
	rewind(plik);
	return -2;
}

int vertNum(FILE *plik)
{
	int n=0;
	char buff[MAX_LINE_SIZE];
	while(fgets(buff, MAX_LINE_SIZE, plik)!=NULL)
	{
		n++;
	}
	rewind(plik);
	return n;
}
