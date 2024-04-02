#include <stdlib.h>
#include "MazeReader.h"
#define MAX_LINE_SIZE 2050
#define CROSSCODE 184
#define TURNCODE 240
#define DEADENDCODE 296


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
                                        establishNeighborhood(g,g->n-2,g->n-1);
                                if((tmp=browseBuforedNumber(l,g,i))!=-1){

                                        establishNeighborhood(g,g->n-1,tmp);
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

                                        establishNeighborhood(g,g->n-1,tmp);
                                        l=removeFromList(l,tmp);

                                }

                        }
                        else if(curr[i-1]==' '){

                                establishNeighborhood(g,g->n-2,g->n-1);
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
                                                establishNeighborhood( g,g->n-2,g->n-1);
                                                if((l=addToList(l,g->n-1))==NULL){
                                                        return 1;
                                                }
                                        }
                                }
                                else{

                                        if(prev[i]==' '){
                                                addVert(g,i,x);
                                                if((tmp=browseBuforedNumber(l,g,i))!=-1){

                                                        establishNeighborhood(g,g->n-1,tmp);
                                                        l=removeFromList(l,tmp);

                                                }
                                        if(curr[i-1]==' ')
                                                establishNeighborhood( g,g->n-2,g->n-1);
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
                                                establishNeighborhood( g,g->n-2,g->n-1);
                                                if(prev[i]==' '){
                                                int tmp;
                                                if((tmp=browseBuforedNumber(l,g,i))!=-1){

                                                        establishNeighborhood(g,g->n-1,tmp);
                                                        l=removeFromList(l,tmp);

                                                }

                                                }
                                        }
                                        else{
                                                int tmp;
                                                if((tmp=browseBuforedNumber(l,g,i))!=-1){

                                                        establishNeighborhood(g,g->n-1,tmp);
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
