#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#define BUFSIZE 128

int number_oct;
char prompt[BUFSIZE];


char newPrompt[BUFSIZE];

	
void Welcome() {
	char *buf;
	buf="\nBienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\nenseash % ";
	int count_buf;
	count_buf=70; //number of characters in buf
	
	write(STDOUT_FILENO,buf,count_buf); //to write buf
}	

void getPrompt() {	
	
	int count_prompt;	
	count_prompt=BUFSIZE;
	number_oct=read(STDOUT_FILENO,prompt,count_prompt);//reading of the prompt in "prompt"
}

void Exec(char *command) {
	pid_t ret;
	int status;
	char *command_exit="exit";
	int size_exit=4;
	char *bye="Bye bye...\n";
	int count_bye=11;
	int len_command=strnlen(command,BUFSIZE);
	int compare=strncmp(command,command_exit,len_command-1); //0 if command and command_exit are the same
	command[len_command-1]='\0'; //to suppress the character created when we press "enter"
	if ((compare==0 && len_command-1==size_exit)||(number_oct==0)) { //if exit is written, si number oct==0, It significate end of file, which is what Ctrl+D tell
			write(STDOUT_FILENO,bye,count_bye);
			exit(EXIT_SUCCESS);
		}
	
	ret=fork();
	if (ret<0) { // if there is a problem
		exit(EXIT_FAILURE); 
	}
	if (ret==0) { //in the son process
		execlp(command, command,NULL); //execution of the command written in the prompt
		exit(EXIT_FAILURE); 
		
		
	}
	if (ret>0) { //in the father process
		
			wait(&status); //waiting for the son process to finish
			if (WIFEXITED(status)) {
				sprintf(newPrompt,"enseash [exit:%d] $",WEXITSTATUS(status));
			} else if(WIFSIGNALED(status)) {
				sprintf(newPrompt,"enseash [sign:%d] $",WTERMSIG(status));
			}
			//exit(EXIT_SUCCESS);
		}
	}
	
void EnterPrompt() { //to add a lign before the writing of the next prompt
	
	int count_newPrompt=19; //number of characters in buf
	
	write(STDOUT_FILENO,newPrompt,count_newPrompt); //to write buf
}	

	

int main() {
	
	Welcome();
	
	while (1) {
		
		getPrompt();
		Exec(prompt);
		EnterPrompt();
		
		

	}
	return 0;

}

 

	
