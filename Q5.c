#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#define BUFSIZE 128
char *buf;
int count_buf, count_prompt, number_oct;
char prompt[BUFSIZE];
pid_t pid;
pid_t pid_son;
pid_t ret;
int status;
int count_time_start;
char newPrompt[BUFSIZE];
struct timespec res; //to read the time
clockid_t clk_id=CLOCK_MONOTONIC;//choice of the clock
int divis=100000;
	
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
	int count_time;
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
		sleep(1);
		execlp(command, command,NULL); //execution of the command written in the prompt
		
		exit(EXIT_FAILURE); 
		
		
	}
	if (ret>0) { //in the father process
			clock_gettime(clk_id,&res); //
			count_time_start=res.tv_nsec;
			wait(&status); //waiting for the son process to finish
			clock_gettime(clk_id,&res);
			count_time=(res.tv_nsec-count_time_start)/divis;
			if (WIFEXITED(status)) {
				sprintf(newPrompt,"enseash [exit:%d|%d ms] $",WEXITSTATUS(status),count_time);
			} else if(WIFSIGNALED(status)) {
				sprintf(newPrompt,"enseash [sign:%d|%d ms] $",WTERMSIG(status),count_time);
			}
			//exit(EXIT_SUCCESS);
		}
	}

	
void EnterPrompt() { //to add a lign before the writing of the next prompt
	
	int count_newPrompt=30; //number of characters in buf
	
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

 

	
