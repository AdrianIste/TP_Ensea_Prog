#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFSIZE 516
char *name;
char *file;
struct addrinfo *res;
char* req;
int ACK1;
int ACK2;





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
void receiveACK(int path) { //getting the ACK
	char ACK[BUFSIZE];
	int lenACK;
	char *errACK="error receiving ACK";
	int lenErrACK=strnlen(errACK,BUFSIZE);

	

	
		lenACK=recvfrom(path,ACK,BUFSIZE,0,res->ai_addr,&(res->ai_addrlen));
		

			if (lenACK==-1) {
				write(STDOUT_FILENO,errACK,lenErrACK);
				exit(EXIT_FAILURE);
			}
			ACK1=ACK[2];
			ACK2=ACK[3];
			
				
					
	
}

void Request(char* fileEntered, int path) { //create the request following RFC1350
	req=malloc(BUFSIZE);
	char* mode;
	int err;
	int lenReq;
	char* errSend="error sending \n";
	int lenErrSend=strnlen(errSend,BUFSIZE);


	
	mode=malloc(BUFSIZE);
	strncpy(mode,"octet",BUFSIZE);

	size_t lenMode=strnlen(mode,BUFSIZE);

	size_t lenFile=strnlen(fileEntered,BUFSIZE);
	
	req[0]=0;
			

	req[1]=2;//2 for WRQ

	strncpy(req+2,fileEntered,BUFSIZE);
	req[lenFile+2]=0;
	strncpy(req+lenFile+1+2,mode,BUFSIZE);
	req[lenMode+lenFile+1+2]=0;
	lenReq=4+lenMode+lenFile;
	err=sendto(path,req,lenReq,0,res->ai_addr,res->ai_addrlen);
				//write(STDOUT_FILENO, req,BUFSIZE);

	if (err==-1) {
		write(STDOUT_FILENO,errSend,lenErrSend);
		exit(EXIT_FAILURE);
	}
	receiveACK(path);


	//free(mode);
	
	


}

void sendWRQ(char ack1, char ack2, int path) { //to send the data
	char *data;
	data=malloc(BUFSIZE);
	int bytesRead;
	int lenData;
	char* errSend="erreur ACK \n";
	int lenErrSend=strnlen(errSend,BUFSIZE);
	int fileDescriptor = open(file, O_RDONLY);
    if (fileDescriptor == -1) {
        write(STDOUT_FILENO,"erreur",6);
        exit(EXIT_FAILURE);
    }
	data[0]=0;
	data[1]=3;
	data[2]=ack1;
	data[3]=ack2;
	
	
	while(1) {
		bytesRead=read(fileDescriptor,data+4,BUFSIZE-4);
		printf("%s bytes%d \n", data+4, bytesRead);
		if (bytesRead==-1) {
			exit(EXIT_FAILURE);
		}
		lenData=sendto(path, data,bytesRead+4,0,res->ai_addr,res->ai_addrlen);
		printf("%d", lenData);
		if (lenData==-1) {
			write(STDOUT_FILENO,errSend,lenErrSend);
			exit(EXIT_FAILURE);
			}
			else if (lenData==0) {
				break;
			}
			if (lenData<BUFSIZE) {
				receiveACK(path);
				break;
			}
			receiveACK(path);

			
				
}
free(data);
}
	

	
	
int main (int argc, char *argv[]) {
	
	int socketPath;
	getInfo(argv[1],argv[2]);
	getAddr(name,file);


	socketPath=getSocket();
	
	Request(file,socketPath);
	sendWRQ(ACK1,ACK2,socketPath);
		

	

	
	
	free(name);
	free(file);
	free(req);
	
}
