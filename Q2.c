#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#define BUFSIZE 128
char *buf;
int count_buf, count_prompt, number_oct;
char prompt[BUFSIZE];
pid_t pid;
pid_t pid_son;
pid_t ret;
int status;
	
void Welcome() {
	buf="\nBienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\nenseash % ";
	count_buf=70; //number of characters in buf
	
	write(STDOUT_FILENO,buf,count_buf); //to write buf
}	

void getPrompt() {
	count_prompt=BUFSIZE;
	number_oct=read(STDOUT_FILENO,prompt,count_prompt);//reading of the prompt in "prompt"
}

void Exec(char *command) {
	int len_command=strnlen(command,BUFSIZE);
	command[len_command-1]='\0'; //to suppress the character created when we press "enter"
	ret=fork();
	if (ret<0) { // if there is a problem
		exit(EXIT_FAILURE);
	}
	if (ret==0) { //in the son process
		execlp(command, command,NULL); //execution of the command written in the prompt
		exit(EXIT_SUCCESS);
	}
	if (ret>0) { //in the father process
	
		wait(&status);
	}
}
	

int main() {
	
	
	
	while (1) {
		Welcome();
		getPrompt();
		Exec(prompt);
		
		

	}
	return 0;

}

 

	
