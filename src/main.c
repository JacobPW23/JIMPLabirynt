#include "MazeReader.h"
#include <stdio.h>
#include<stdlib.h>
#include <unistd.h>
int main(int argc,char** argv){
	int c;
	char* graph_file=NULL;
	while((c=getopt(argc,argv,"hs:"))!=-1)
	{

		switch(c){

			case 'h':{
					printf("Rozwiązywanie labiryntu w formacie grafu\n");
					printf("Opcje:\n");
					printf("s - plik grafu opisującego labirynt\n");
					printf("h - pomoc\n");
					break;
				 }
			case 's':
				 {

					graph_file=optarg;
					break;
					

				 }

			
		}


	}
	if(graph_file!=NULL){
		FILE* out=fopen(graph_file,"w");
		if(out==NULL){
		fprintf(stderr,"Błąd 1 Nie udało się otworzyć pliku lub plik nie istnieje.\n");
		
		}
		fclose(out);
	}
	

return 0;
}
