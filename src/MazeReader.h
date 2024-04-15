#ifndef MAZE_READER
#define MAZE_READER 
#include "Graph.h"

typedef struct header
{
        int file_id;
        char esc;
        short cols;
        short lines;
        short entry_x;
        short entry_y;
        short exit_x;
        short exit_y;
        int reserved[3];
        int counter;
        int solution_offset;
        char separator;
        char wall;
        char path;
}header;



int validFile(FILE * file);
int assembleGraph(Graph g,char * filename);
int readRLE8File(char* file_name);

void writeToHeader(header *header, int file_id, int esc, int cols, int lines, int entry_x, int entry_y, int exit_x, int exit_y, int reserved, int counter, int solution_offset, int separator, int wall, int path);
void writeSymbol(FILE *plik, char value, int count, char separator);
int colNum(FILE *plik);
int lineNum(FILE *plik);
int entry_x(FILE *plik);
int entry_y(FILE *plik);
int exit_x(FILE *plik);
int exit_y(FILE *plik);
int compressToBin(header *header, FILE *plik, FILE *out);



#endif
