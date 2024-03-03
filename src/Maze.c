#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Maze.h"
#define MAX_LINE_SIZE 2050

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
				//we've got a pleasure with crossroads
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
			//we've got a pleasure with a "dead end"
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
				//we've got a pleasure with 90 degree turn
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

				//we've got a pleasure with start/end vertice in default maze configuration location
				//other locations will be served in previous code cases
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

void wypisz(Stack *stack, Graph graph)
{
    Node *temp=stack->top;
    while(temp!=NULL && temp->next!=NULL)
    {
        if(graph->cords[2*(temp->node)] == graph->cords[2*(temp->next->node)])
        {
            if(graph->cords[2*(temp->node)+1] > graph->cords[2*(temp->next->node)+1])
                printf("Góra %d ", graph->cords[2*(temp->node)+1]-graph->cords[2*(temp->next->node)+1]);
            else if(graph->cords[2*(temp->node)+1] < graph->cords[2*(temp->next->node)])
                printf("Dół %d ", graph->cords[2*(temp->next->node)]-graph->cords[2*(temp->node)+1]);
        }
	
        else if(graph->cords[2*(temp->node)+1] == graph->cords[2*(temp->next->node)+1])
        {
            if(graph->cords[2*(temp->node)] > graph->cords[2*(temp->next->node)])
                printf("Lewo %d ", graph->cords[2*(temp->node)]-graph->cords[2*(temp->next->node)]);
            else if(graph->cords[2*(temp->node)] < graph->cords[2*(temp->next->node)])
                printf("Prawo %d ", graph->cords[2*(temp->next->node)]-graph->cords[2*(temp->node)]);
        }
        else 
            printf("Błąd\n");

	temp=temp->next;
	}
}
void printVertToStream(FILE * stream,Graph g){
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
}

int* readVertFromStream(char* filename,int n){
	FILE * stream=fopen(filename,"r");
	if(stream==NULL){

	return NULL;
	}	
	char tmp [100];int dummy;
	for(int i=0;i<n;i++){
		fgets(tmp,100,stream);
	
	}
	fclose(stream);
	int* vert;
		if((vert=malloc(5 * sizeof*vert))==NULL){

			return NULL;

	}
	memset(vert,-1,4*sizeof*vert);
	if(sscanf(tmp,"%d %d %d %d %d %d %d",&dummy,&dummy,vert,vert+1,vert+2,vert+3,vert+4)<3){
		free(vert);
		return NULL;
	
	}	
	return vert;
}

