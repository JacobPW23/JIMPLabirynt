#include <stdio.h>
#include <string.h>
#include "Graph.h"
#include "GraphWriter.h"
#include "MazeReader.h"
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


int readRLE8File(char* file_name)
{
	char bin[5]=".bin";
	char txt[5]=".txt";
	char file_name_bin[50]="";
	strcat(file_name_bin, file_name);
	strcat(file_name_bin, bin);
        FILE *plik = fopen(file_name_bin, "rb");
        if(plik==NULL)
        {
                printf("Nie udało się otworzyć pliku\n");
                return 1;
        }
	
	int file_id;
        int esc;
        int columns;
        int lines;
        int entry_x, entry_y;
        int exit_x, exit_y;
        int counter;
        int solution_offset;
        int separator;
        int wall, path;


        fread(&file_id, 4, 1, plik);
        fread(&esc, 1, 1, plik);
        fread(&columns, 2, 1, plik);
        fread(&lines, 2, 1, plik);
        fread(&entry_x, 2, 1, plik);
        fread(&entry_y, 2, 1, plik);
        fread(&exit_x, 2, 1, plik);
        fread(&exit_y, 2, 1, plik);
	
        fseek(plik, 12, SEEK_CUR);

        fread(&counter, 4, 1, plik);
        fread(&solution_offset, 4, 1, plik);
        fread(&separator, 1, 1, plik);
        fread(&wall, 1, 1, plik);
        fread(&path, 1, 1, plik);
	
        int value;
        int count;

        int charInLine=0;
        int currPos=1;
        int lineNumber=1;

	char file_name_txt[50]="";
	strcat(file_name_txt, file_name);
	strcat(file_name_txt, txt);	
        FILE *txtplik=fopen(file_name_txt, "w");
	
	if(txtplik==NULL)
	{
		printf("Nie udało się otworzyć pliku .txt\n");
		return 2;
	}

        while(lineNumber<=lines)
        {
                while(charInLine < columns)
                {
                        fread(&separator, 1, 1, plik);
                        fread(&value, 1, 1, plik);
                        fread(&count, 1, 1, plik);
                        charInLine+=count+1;
                        while(currPos<=charInLine)
                        {
                                if(currPos==entry_x&&lineNumber==entry_y)
                                {
                                        putc('P', txtplik);
                                        currPos++;
                                }
                                else if(currPos==exit_x&&lineNumber==exit_y)
                                {
                                        putc('K', txtplik);
                                        currPos++;
                                }
				else
				{
					if(value==wall)
                                		putc(88, txtplik);
					else if(value==path)
						putc(32, txtplik);
					else
					{
						printf("Błąd formatu pliku binarnego\n");
						return 3;
					}
					currPos++;
					
				}
                        }

                }
		putc('\n', txtplik);
                lineNumber++;
                currPos=1;
                charInLine=0;

        }
	fclose(txtplik);
	
	FILE *txtfile=fopen(file_name_txt, "r");
	if(validFile(txtfile)==1)
		return 4;

	printf("Przetworzono format pliku na tekstowy\n");
	return 0;
	
}

int assembleGraph(Graph g,char * filename)
{
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

