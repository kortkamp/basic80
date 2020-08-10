#include "file.h"



void load(char *filename){

	FILE *fp;

	char linebuffer[255];

	fp = fopen(filename,"r");
	if(fp == NULL){
		error = FILEERROR;
		return;
	}
	// Clean Program space.
	new();

	while(fscanf(fp,"%[^\n]\n",linebuffer) != EOF){
		//printf("%s\n",linebuffer);
		enter_line(linebuffer);
		if(ferror(fp)){
			error = FILEERROR;
			return;		
		}
	}

	fclose(fp);



}
