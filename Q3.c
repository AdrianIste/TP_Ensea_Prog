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
	char *command_exit="exit";
	int size_exit=4;
	char *command_EOF="EOF";
	int size_EOF=3;
	
	char *bye="Bye bye...\n";
	int count_bye=11;
	int len_command=strnlen(command,BUFSIZE);
	int compare=strncmp(command,command_exit,len_command-1); //0 if command and command_exit are the same
	int compare2=strncmp(command,command_EOF,len_command-1);
	command[len_command-1]='\0'; //to suppress the character created when we press "enter"
	ret=fork();
	if (ret<0) { // if there is a problem
		exit(EXIT_FAILURE);
	}
	if (ret==0) { //in the son process
		execlp(command, command,NULL); //execution of the command written in the prompt
		//exit(EXIT_SUCCESS);
	}
	if (ret>0) { //in the father process
		if (compare==0 && len_command-1==size_exit) { //if exit is written
			write(STDOUT_FILENO,bye,count_bye);
			exit(EXIT_SUCCESS);
		}
		else {
			wait(&status); //waiting for the son process to finish
			//exit(EXIT_SUCCESS);
		}
	}
}
	

int main() {
	
	Welcome();
	
	while (1) {
		
		getPrompt();
		Exec(prompt);
		
		

	}
	return 0;

}

 

	
