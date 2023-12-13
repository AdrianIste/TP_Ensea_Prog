#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char *name;
char *file;


void getInfo(char *name1, char *file1) { //to take the names from the arguments
	size_t lenName=strlen(name1);
	size_t lenFile=strlen(file1);
	name=malloc(lenName);
	file=malloc(lenFile-1);////////////////////////
	strcpy(file,file1);
	strcpy(name,name1);
}

int main (int argc, char *argv[]) {
	getInfo(argv[1],argv[2]);
	
	free(name);
	free(file);
}
