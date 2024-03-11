#include "Maze.h"
#include <stdio.h>
#include<stdlib.h>
int main(int argc,char** argv){

	if(argc>1){
		char * buff[2050];
		FILE * mazefile = fopen(argv[1],"r");
		validFile(mazefile);
		fclose(mazefile);
	}

return 0;
}
