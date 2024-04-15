#include "MazeReader.h"
#include "GraphWriter.h"
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include <unistd.h>
#define HELP_PRINT() \
	printf("Preprocesor formatujący labirynt do postaci grafu\n");\
	printf("Opcje:\n");\
	printf("-m - nazwa pliku z labiryntem w formacie pierwotnym (bez rozszerzenia)\n");\
	printf("-f - nazwa pliku zawierającego graf opisujący labirynt\n");\
	printf("-c - wskazuje,że plik podany w parametrze m jest skompresowany do RLE8\n");\
	printf("-h - pomoc\n");

int main(int argc,char** argv){
	int c;
	char* maze_file=NULL;
	char* format_file=NULL;
	int decompress=0;
	int compress=0;
	if(argc==1){
		HELP_PRINT();
	}
	while((c=getopt(argc,argv,"dchm:f:"))!=-1)
	{
		switch(c){

			case 'h':{
					 HELP_PRINT(); break;
				 }
			case 'm':
				 {
					maze_file=optarg;
					break;	
				 }
			case 'f':{
					format_file=optarg;
					break;
				 }
			case 'd':{
					decompress=1;
					break;
				 }
			case 'c':{
					compress=1;
					break;
				 }
		}


	}
	if(maze_file!=NULL && format_file!=NULL){
		FILE* out=fopen(format_file,"w");
		Graph gr;
		if(( gr=initGraph())==NULL){
			return 1;	
		}
		char* binfile=malloc(strlen(maze_file)+5);
		strcpy(binfile,maze_file);
		char* txtfile=strcat(maze_file,".txt");
		if(compress)
		{
			FILE *plik=fopen(txtfile, "r");
			if(plik==NULL)
			{
				printf("Nie udało się otworzyć pliku\n");
				return 1;
			}
			header *header=malloc(sizeof *header);
			writeToHeader(header, 123, 32, colNum(plik), 
				      lineNum(plik), entry_x(plik), entry_y(plik), 
				      exit_x(plik), exit_y(plik), 
				      0, 1000, 0, '#', 'X', ' ');
			compressToBin(header, plik, out);
			free(header);
			return 0;
		}
		if(decompress){
			if(readRLE8File(binfile)){

				fprintf(stderr,"Błąd: Nie udało się zdekompresować pliku\n");
				return 1;
			}
		}
		
		if(assembleGraph(gr,txtfile)!=0){
			fclose(out);
			freeGraph(gr);
			return 1;
		}
		printGraphToStream(out,gr);
	
		fclose(out);
		freeGraph(gr);
		free(binfile);
	}


	return 0;
}
