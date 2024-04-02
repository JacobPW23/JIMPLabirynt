#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "GraphWriter.h"
#define MAX_LINE_SIZE 2050

void printVertToStream(FILE * stream,Graph g){
        fprintf(stream, " %d %d\n", g->start, g->end);
        for(int i=0;i<g->n;i++){
                fprintf(stream,"%d %d",g->coords[2*i],g->coords[2*i+1]);
                for(int j=0;j<4;j++){
                        fprintf(stream," %d", g->neighbors[i][j]);

                }
                fprintf(stream, "\n");
        }
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

