#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>

char *name;
char *file;

void getInfo(char *name1, char *file1) {
	name=name1;
	file=file1;
}

int main (int argc, char *argv[]) {
	getInfo(argv[1],argv[2]);
}

