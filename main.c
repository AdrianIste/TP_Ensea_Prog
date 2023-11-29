
#include <unistd.h>


#define BUFSIZE 128
char buf[BUFSIZE];



int main() {
	write(2,"bonjour",7);
	
	return 0;
}

 

	
