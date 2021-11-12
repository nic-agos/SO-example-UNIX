#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

/*SIGCHLD di default non fa terminare l'applicazione ma invia soltanto la segnalazione al parent della sua terminazione*/
int main(int a, char **b){

	int i;
	
#ifdef IGNORE
	/*da ora in poi voglio ignorare esplicitamente la terminazione di ogni figlio, così che
	 il kernel non mantiene in stato zombie il thread (elimina i suoi metadati, tra cui il codice di terminazione)*/
	signal(SIGCHLD,SIG_IGN); //in caso di ricezione di evento SIGCHLD ignora il segnale esplicitamente (SIG_IGN)
#endif

	for (i=0; i<10; i++){
		if(fork() == 0) { //sono nel child
			exit(0); // il child termina con il codice di terminazione 0, entrano in stato zombie se non compilo con ignore
		}
	}

	pause();

}
