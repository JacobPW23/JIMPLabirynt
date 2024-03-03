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
					printf("Graph format maze preprocesor\n");
					printf("Options:\n");
					printf("m - maze txt filename\n");
					printf("f - result graph format filename\n");
					printf("h - help\n");
				 }
			case 'm':
				 {

					maze_file=optarg;
					

				 }
			case 'f':{

					format_file=optarg;
				 }

			
		}


	}
	if(maze_file!=NULL && format_file!=NULL){
		FILE* out=fopen(format_file,"w");
		if(out==NULL){
			printf("Reading from file imposibble");
			return 1;
		}
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
