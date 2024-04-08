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
	if(argc==1){
		HELP_PRINT();
	}
	while((c=getopt(argc,argv,"chm:f:"))!=-1)
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
			case 'c':{
					decompress=1;
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
		if(decompress){
		if(readRLE8File(binfile)){

			fprintf(stderr,"Błąd: Nie udało się zdekompresować pliku\n");
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
