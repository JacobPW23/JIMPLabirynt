#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "GraphWriter.h"
#define MAX_LINE_SIZE 2050

void printGraphToStream(FILE * stream,Graph g){
        fprintf(stream, " %d %d\n", g->start, g->end);
        for(int i=0;i<g->n;i++){
                fprintf(stream,"%d %d",g->coords[2*i],g->coords[2*i+1]);
                for(int j=0;j<4;j++){
                        fprintf(stream," %d", g->neighbors[i][j]);

                }
                fprintf(stream, "\n");
        }
}


