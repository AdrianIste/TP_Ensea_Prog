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




void getInfo(char *nameEntered, char *fileEntered) { //to take the names from the terminal
	
	size_t lenName=strnlen(nameEntered,BUFSIZE);
	size_t lenFile=strnlen(fileEntered,BUFSIZE);
	
	name=malloc(lenName);
	file=malloc(lenFile);////////////////////////
	//fileEntered[lenFile-1]='\0';
	strncpy(file,fileEntered,lenFile);
	strncpy(name,nameEntered,lenName);
	
}
void getAddr(char *domain, struct addrinfo *res) { //to take the address
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
int getSocket(struct addrinfo *res) {
	
	char *error="error creating socket";
	int socketPath;
	printf("%d %d %d", res->ai_family,res->ai_socktype,res->ai_protocol);
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
	getAddr(name,res);
	printf("nom %s file %s", name, file);

	socketPath=getSocket(res);

	
	
	free(name);
	free(file);
	free(res);
}
