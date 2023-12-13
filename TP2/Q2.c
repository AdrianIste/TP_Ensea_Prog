#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *name;
char *file;
struct sockaddr *address;


void getInfo(char *name1, char *file1) { //to take the names from the arguments
	size_t lenName=strlen(name1);
	size_t lenFile=strlen(file1);
	name=malloc(lenName);
	file=malloc(lenFile-1);////////////////////////
	strcpy(file,file1);
	strcpy(name,name1);
}
void getAddr(char *domain) { //to take the address
	struct addrinfo hints;
	struct addrinfo *res;
	int err;
	int size_info;
	const char *message_error;
	size_info=sizeof(struct addrinfo);
	memset(&hints,0,size_info); //set all elements of struct to 0
	hints.ai_protocol=IPPROTO_UDP;; //filter only UDP
	err=getaddrinfo(domain,NULL,&hints,&res);//fill res with hints fields
	message_error=gai_strerror(err);
	if (err!=0) {
		size_t LenError=strlen(message_error);
		write(STDOUT_FILENO, message_error,LenError);
	}
	else {
	address=res->ai_addr;
	}
}
	
int main (int argc, char *argv[]) {
	getInfo(argv[1],argv[2]);
	getAddr(name);
	
	free(name);
	free(file);
}
