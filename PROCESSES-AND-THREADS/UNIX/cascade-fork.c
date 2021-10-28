#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define NUM_FORKS 10

int main(int a, char ** b){

	int residual_forks = NUM_FORKS;

	another_fork:

	residual_forks--;
	if(fork()>0){  //se fork()>0 sono nel processo padre e vado in pausa
		pause();
	}
	else{ 	// sono il processo figlio
		printf("ciao");
		if(residual_forks>0){	;
		 	goto another_fork;	
		}
	}
	pause();



}
