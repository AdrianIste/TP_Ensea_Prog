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
<<<<<<< HEAD
=======
struct sockaddr *address;
>>>>>>> f57a61e1352c21af259bf5b9fa351222851bafe5




<<<<<<< HEAD
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
=======
void getInfo(char *name1, char *file1) { //to take the names from the 
	
	size_t lenName=strnlen(name1,BUFSIZE);
	printf("%ld\n", lenName);
	size_t lenFile=strnlen(file1,BUFSIZE);
	
	name=malloc(lenName);
	file=malloc(lenFile);////////////////////////
	strncpy(file,file1,lenFile-1);
	strncpy(name,name1,lenName);
	
}
void getAddr(char *domain, struct addrinfo *res) { //to take the address

>>>>>>> f57a61e1352c21af259bf5b9fa351222851bafe5
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
	
<<<<<<< HEAD
=======
	else {
	address=res->ai_addr;
	}
>>>>>>> f57a61e1352c21af259bf5b9fa351222851bafe5
}
int getSocket(struct addrinfo *res) {
	
	char *error="error creating socket";
	int socketPath;
<<<<<<< HEAD
	printf("%d %d %d", res->ai_family,res->ai_socktype,res->ai_protocol);
	socketPath=socket(res->ai_family, res->ai_socktype, res->ai_protocol); //put the socket int socketPath, return -1 if error
=======
	socketPath=socket(res->ai_family, res->ai_socktype, res->ai_protocol);
>>>>>>> f57a61e1352c21af259bf5b9fa351222851bafe5
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
<<<<<<< HEAD
=======
	char *CsocketPath;
>>>>>>> f57a61e1352c21af259bf5b9fa351222851bafe5
	struct addrinfo *res=malloc(sizeof(struct addrinfo));
	
	getInfo(argv[1],argv[2]);
	getAddr(name,res);
	printf("nom %s file %s", name, file);

	socketPath=getSocket(res);
<<<<<<< HEAD

=======
	//sprintf(CsocketPath, "%d", socketPath);
	//write(STDOUT_FILENO, CsocketPath,strlen(CsocketPath));
>>>>>>> f57a61e1352c21af259bf5b9fa351222851bafe5
	
	
	free(name);
	free(file);
	free(res);
}
