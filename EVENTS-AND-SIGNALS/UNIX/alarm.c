#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>

#define timeout 2

void wakeup(int sgnumber){
	printf("I'm awake\n");
	alarm(timeout); 
	/*il flusso una volta eseguito il gestore dell'evento ritorna nel while(1) 
	 cioè dove aveva interroto l'esecuzione all'arrivo del segnale */

	
}

int main (int argc, char**argv){

	signal(SIGALRM, wakeup);  //imposto la funzione di gestione della sveglia, altrimenti il comportamento di defualt farebbe chiudere l'applicazione
	alarm(timeout);  //invoco l'invio del segnale SIGALRM a noi stessi
	
	while (1){
		pause(); //pause() è una syscall bloccante che verrà sbloccata solo per effetto di una segnalazione
	}	

}
