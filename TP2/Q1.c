#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define BUFSIZE 128

char *name;
char *file;


void getInfo(char *nameEntered, char *fileEntered) { //to take the names from the arguments
	size_t lenName=strnlen(nameEntered,BUFSIZE);
	size_t lenFile=strnlen(fileEntered,BUFSIZE);
	name=malloc(lenName);
	file=malloc(lenFile);
	strncpy(file,fileEntered,lenFile);
	strncpy(name,nameEntered,lenName);
}

int main (int argc, char *argv[]) {
	getInfo(argv[1],argv[2]);
	
	free(name);
	free(file);
}
