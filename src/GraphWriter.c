#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "GraphWriter.h"
#define MAX_LINE_SIZE 2050

void printVertToStream(FILE * stream,Graph g){
        fprintf(stream, " %d %d\n", g->start, g->end);
        for(int i=0;i<g->n;i++){
                fprintf(stream,"%d %d",g->cords[2*i],g->cords[2*i+1]);
                for(int j=0;j<4;j++){
                        fprintf(stream," %d", g->neighbours[i][j]);

                }
                fprintf(stream, "\n");
        }
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

