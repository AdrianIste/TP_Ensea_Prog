#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFSIZE 516 //512 bytes of data + 4 bytes of header
#define DATASIZE 512
char *name;
char *file;
struct addrinfo *res;
char* req;
int ACK1;
int ACK2;





void getInfo(char *nameEntered, char *fileEntered) { //to take the names from the terminal

	size_t lenName=strnlen(nameEntered,BUFSIZE);
	size_t lenFile=strnlen(fileEntered,BUFSIZE);

	name=malloc(lenName+1); //+1 for the '\0' at the end of the string
	file=malloc(lenFile+1);
	strncpy(file,fileEntered,lenFile);
	strncpy(name,nameEntered,lenName);
	file[lenFile]='\0';
	name[lenName]='\0';

}
void getAddr(char *domain, char * fileEntered) { //to take the address
	struct addrinfo hints;
	int err;
	int size_info;
	const char *message_error;



	size_info=sizeof(struct addrinfo);
	memset(&hints,0,size_info); //set all elements of struct to 0
	hints.ai_protocol=IPPROTO_UDP; //filter only UDP
	err=getaddrinfo(domain,"1069",&hints,&res);//fill res with hints fields


	if (err!=0) {
		message_error=gai_strerror(err);
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




		lenACK=recvfrom(path,ACK,BUFSIZE,0,res->ai_addr,&(res->ai_addrlen)); //the server answers from a new port, res is updated with it


			if (lenACK==-1) {
				write(STDOUT_FILENO,errACK,lenErrACK);
				exit(EXIT_FAILURE);
			}
			ACK1=(unsigned char)ACK[2]; //unsigned char to avoid negative values when the block number is > 127
			ACK2=(unsigned char)ACK[3];
			printf("ACK1 %d ACK2 %d \n",ACK1, ACK2);




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

	strncpy(req+2,fileEntered,BUFSIZE-2);
	req[lenFile+2]=0;
	strncpy(req+lenFile+1+2,mode,BUFSIZE-lenFile-3);
	req[lenMode+lenFile+1+2]=0;
	lenReq=4+lenMode+lenFile;
	err=sendto(path,req,lenReq,0,res->ai_addr,res->ai_addrlen);

	if (err==-1) {
		write(STDOUT_FILENO,errSend,lenErrSend);
		exit(EXIT_FAILURE);
	}
	receiveACK(path); //the server answers with ACK 0 if it accepts the request


	free(mode);




}

void sendWRQ(int path) { //to send the data
	char *data;
	data=malloc(BUFSIZE);
	int bytesRead;
	int lenData;
	int block=1; //the first data block has the number 1 (RFC1350)
	char* errSend="erreur envoi \n";
	int lenErrSend=strnlen(errSend,BUFSIZE);
	char* errACK="erreur ACK \n";
	int lenErrACK=strnlen(errACK,BUFSIZE);
	int fileDescriptor = open(file, O_RDONLY);
    if (fileDescriptor == -1) {
        write(STDOUT_FILENO,"erreur",6);
        exit(EXIT_FAILURE);
    }
	data[0]=0;
	data[1]=3; //3 for DATA


	while(1) {
		data[2]=(block>>8) & 0xFF; //block number on 2 bytes : first byte
		data[3]=block & 0xFF; //second byte
		bytesRead=read(fileDescriptor,data+4,DATASIZE); //max 512 bytes of data after the header
		if (bytesRead==-1) {
			exit(EXIT_FAILURE);
		}
		lenData=sendto(path, data,bytesRead+4,0,res->ai_addr,res->ai_addrlen);
		printf("block %d : %d bytes sent \n", block, lenData);
		if (lenData==-1) {
			write(STDOUT_FILENO,errSend,lenErrSend);
			exit(EXIT_FAILURE);
			}
		receiveACK(path);
		if (ACK1*256+ACK2!=block) { //the server must acknowledge the block we just sent
			write(STDOUT_FILENO,errACK,lenErrACK);
			exit(EXIT_FAILURE);
		}
		if (bytesRead<DATASIZE) { //a block smaller than 512 bytes means it is the last one
			break;
		}
		block++; //next block

}
close(fileDescriptor);
free(data);
}




int main (int argc, char *argv[]) {

	int socketPath;
	if (argc!=3) { //we need the server and the file
		printf("usage : %s <server> <file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	getInfo(argv[1],argv[2]);
	getAddr(name,file);


	socketPath=getSocket();

	Request(file,socketPath);
	sendWRQ(socketPath);






	close(socketPath);
	freeaddrinfo(res);
	free(name);
	free(file);
	free(req);

}
