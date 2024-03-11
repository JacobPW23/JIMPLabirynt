#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MazeReader.h"
#define MAX_LINE_SIZE 2050
int* readVertFromStream(FILE * stream,int n){
	
	if(stream==NULL){

	return NULL;
	}	
	char tmp [100];int dummy;
	for(int i=0;i<=n;i++){
		fgets(tmp,100,stream);
	
	}
	rewind(stream);
	int* vert;
		if((vert=malloc(5 * sizeof*vert))==NULL){
			fprintf(stderr,"Zabrakło pamięci na dalsze procedowanie rozwiązania\n");
			return NULL;

	}
	memset(vert,-1,4*sizeof*vert);
	if(sscanf(tmp,"%d %d %d %d %d %d %d",&dummy,&dummy,vert,vert+1,vert+2,vert+3,vert+4)<3){
		free(vert);
		fprintf(stderr,"Niepoprawna liczba elementów w linii %d w pliku\n",n);
		return NULL;
	
	}	
	return vert;
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

