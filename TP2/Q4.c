#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFSIZE 516
char *name;
char *file;
struct addrinfo *res;
char* req;





void getInfo(char *nameEntered, char *fileEntered) { //to take the names from the terminal
	
	size_t lenName=strnlen(nameEntered,BUFSIZE);
	size_t lenFile=strnlen(fileEntered,BUFSIZE);
	
	name=malloc(lenName);
	file=malloc(lenFile);
	strncpy(file,fileEntered,lenFile);
	strncpy(name,nameEntered,lenName);
	
}
void getAddr(char *domain, char * fileEntered) { //to take the address
	struct addrinfo hints;
	int err;
	int size_info;
	const char *message_error;


	
	size_info=sizeof(struct addrinfo);
	memset(&hints,0,size_info); //set all elements of struct to 0
	hints.ai_protocol=IPPROTO_UDP;; //filter only UDP
	err=getaddrinfo(domain,"1069",&hints,&res);//fill res with hints fields
	message_error=gai_strerror(err);
	
	
	if (err!=0) {
		size_t LenError=strlen(message_error);
		write(STDOUT_FILENO, message_error,LenError);
		exit(EXIT_FAILURE);
	}
	
	
}
int getSocket() { //getting the socket following the address we have in res
	
	char *error="error creating socket";
	int socketPath;
	socketPath=socket(res->ai_family, res->ai_socktype, res->ai_protocol); //put the socket int socketPath, return -1 if error
	if (socketPath ==-1) {
		write(STDOUT_FILENO,error,strlen(error));
		exit(EXIT_FAILURE);
	}
	else {
	return socketPath;
}
}

void createRequest(char* fileEntered, int path) { //create the request following RFC1350
	req=malloc(BUFSIZE);
	char* mode;
	int err;
	int lenReq;


	
	mode=malloc(BUFSIZE);
	strncpy(mode,"octet",BUFSIZE);

	size_t lenMode=strnlen(mode,BUFSIZE);

	size_t lenFile=strnlen(fileEntered,BUFSIZE);
	
	req[0]=0;
			

	req[1]=1;

	strncpy(req+2,fileEntered,BUFSIZE);
	req[lenFile+2]=0;
	strncpy(req+lenFile+1+2,mode,BUFSIZE);
	req[lenMode+lenFile+1+2]=0;
	lenReq=4+lenMode+lenFile;
	err=sendto(path,req,lenReq,0,res->ai_addr,res->ai_addrlen);
				//write(STDOUT_FILENO, req,BUFSIZE);

	if (err==-1) {
		write(STDOUT_FILENO,"errorSend",9);
		exit(EXIT_FAILURE);
	}


	//free(mode);
	
	


}

void sendACK(char data1, char data2, int path) { //to send the acknowledgment
	char *ackReq;
	int err;
	ackReq=malloc(BUFSIZE);
	ackReq[0]=0;
	ackReq[1]=4;
	ackReq[2]=data1;
	ackReq[3]=data2;
	
	size_t lenackReq=4;

	err=sendto(path, ackReq,lenackReq,0,res->ai_addr,res->ai_addrlen);
	if (err==-1) {
		write(STDOUT_FILENO,"erreurack",9);
		exit(EXIT_FAILURE);
	}
	free(ackReq);
}
	
void receiveData(int path) { //to stock the data received
	char data[BUFSIZE];
	int lenData=BUFSIZE;

	while(1) {
		lenData=recvfrom(path,data,BUFSIZE,0,res->ai_addr,&(res->ai_addrlen));


		printf("%d \n",lenData);
			if (lenData==-1) {
				write(STDOUT_FILENO,"errorReceive",12);
				exit(EXIT_FAILURE);
			}
			else if (lenData==0){
						printf("%d",lenData);


			}
			else {

				sendACK(data[2],data[3], path);
			if (lenData<BUFSIZE) {
				break;
			}
				
			}
		}
				
					
	
}
	
	
int main (int argc, char *argv[]) {
	
	int socketPath;
	
	getInfo(argv[1],argv[2]);
	getAddr(name,file);

	socketPath=getSocket();
	//printf("nom %s file %s socket %d \n", name, file,socketPath);
	
	createRequest(file,socketPath);
		

	receiveData(socketPath);


	
	
	free(name);
	free(file);
	free(req);
	
}
