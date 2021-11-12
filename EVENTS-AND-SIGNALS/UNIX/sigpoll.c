#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

#define SLEEP_PERIOD 5

// il comportamento di questa applicazione in caso di ricezione di segnalazione SIGINT è di default, l'applicazione termina ad un arrivo di tale segnale
int main(int argc, char **argv){

  int  i;
  sigset_t set; //bitmask dove posso registrare i segnali da includere/escludere


  sigfillset(&set); //riempie il set con tutti i segnali
  sigprocmask(SIG_BLOCK,&set,NULL);  //blocco la ricezione di tutti i segnali

  while(1) {
		sleep(SLEEP_PERIOD);
		printf("querying the sigset\n");
		sigpending(&set); //chiedo al kernel se ci sono segnali pendenti per questo thread main

		if(sigismember(&set,SIGINT)){
		  sigemptyset(&set); //svuoto l'insieme dei segnali
		  sigaddset(&set,SIGINT); //aggiungo al set soltanto SIGINT
		  sigprocmask(SIG_UNBLOCK,&set,NULL);  //chiedo di sbloccare le segnalazioni di tipo SIGINT
		}
	}
}
