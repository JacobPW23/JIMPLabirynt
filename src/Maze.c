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
			else if((curr[i-1]=='P' || curr[i+1]=='K')&& prev[i]!=nxt[i]){

				//we've got a pleasure with start/end vertice in default maze configuration location
				//other locations will be served in previous code cases
				if(curr[i-1]=='P'){

					addVert(g,i,x);
					if(nxt[i]==' ')
						l=addToList(l,g->n-1);
				}
				else{
					if(curr[i-1]==' '){
						addVert(g,i,x);
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


