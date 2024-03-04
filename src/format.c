#include "Maze.h"
#include <stdio.h>
#include<stdlib.h>
#include <unistd.h>
int main(int argc,char** argv){
	int c;
	char* maze_file=NULL;
	char* format_file=NULL;
	while((c=getopt(argc,argv,"hm:f:"))!=-1)
	{

		switch(c){

			case 'h':{
					printf("Preprocesor formatujący labirynt do postaci grafu\n");
					printf("Opcje:\n");
					printf("m - nazwa pliku z labiryntem w formacie pierwotnym\n");
					printf("f - nazwa pliku zawierającego graf opisujący labirynt\n");
					printf("h - pomoc\n");
					break;
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

			
		}


	}
	if(maze_file!=NULL && format_file!=NULL){
		FILE* out=fopen(format_file,"w");
		Graph gr;
		if(( gr=initGraph())==NULL){
		return 1;	
		}
		if(assembleGraph(gr,maze_file)!=0){
			fclose(out);
			freeGraph(gr);
			return 1;
		}
		printVertToStream(out,gr);

		fclose(out);
		freeGraph(gr);
	}
	

return 0;
}
