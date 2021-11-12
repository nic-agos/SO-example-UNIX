#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int a, char **b){

	int i;
	int value;
	
	for (i=0; i<10; i++){
		if(fork() == 0) pause(); //se sono un child entro in pausa
	}

	signal(SIGINT,SIG_IGN);  // il parent va ad ignorare SIGINT

	for (i=0; i<10; i++){
		wait(&value); // aspetto i processi figlio
		printf("last two bytes of value are %d - %d\n",(value>>8)&255,value&255); // digitando ctrl+c da shell stampa 0 - 2
	}
	

}
