#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFSIZE 128
char *name;
char *file;
struct addrinfo *res;




void getInfo(char *nameEntered, char *fileEntered) { //to take the names from the terminal
	
	size_t lenName=strnlen(nameEntered,BUFSIZE);
	size_t lenFile=strnlen(fileEntered,BUFSIZE);
	
	name=malloc(lenName);
	file=malloc(lenFile);
	strncpy(file,fileEntered,lenFile);
	strncpy(name,nameEntered,lenName);
	
}
void getAddr(char *domain) { //to take the address
	struct addrinfo hints;
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
	
	
}
int getSocket() { //getting the socket following the address we have in res
	
	char *error="error creating socket";
	int socketPath;
	socketPath=socket(res->ai_family, res->ai_socktype, res->ai_protocol); //put the socket int socketPath, return -1 if error
	if (socketPath ==-1) {
		write(STDOUT_FILENO,error,strlen(error));
		return socketPath;
	}
	else {
	return socketPath;
}
}
	
int main (int argc, char *argv[]) {
	
	int socketPath;
	struct addrinfo *res=malloc(sizeof(struct addrinfo));
	
	getInfo(argv[1],argv[2]);
	getAddr(name);

	socketPath=getSocket();
	printf("nom %s file %s socket %d \n", name, file,socketPath);

	
	
	free(name);
	free(file);
	free(res);
}
