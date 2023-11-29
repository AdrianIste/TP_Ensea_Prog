#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define BUFSIZE 128


int main() {
	
	char *buf;
	int count_buf, count_prompt, number_oct;
	char prompt[BUFSIZE];
	
	buf="\nBienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\nenseash %\n";
	count_buf=70; //nombre de caracteres de buf
	count_prompt=BUFSIZE;
	while (1) {
		
		write(STDOUT_FILENO,buf,count_buf);
		number_oct=read(STDOUT_FILENO,prompt,count_prompt); //on stocke dans prompt la chaine de caracere lue et dans number_oct le nombre d octets lus
		write (STDOUT_FILENO,prompt,number_oct); //pour verifier
		

	}
	return 0;

}

 

	
