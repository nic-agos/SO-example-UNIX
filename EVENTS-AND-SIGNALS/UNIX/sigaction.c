#include <stdio.h>
#include <signal.h>
#include <unistd.h>


#define SLEEP_PERIOD 5

void generic_handler(int signal, siginfo_t * a, void *b){

  sigset_t set;

  printf("received signal is %d\n",signal);

}


int main(int argc, char **argv){

  int  i;
  sigset_t set;
  struct sigaction act;


  sigfillset(&set);  //riempio tutti i campi della bitmask

  act.sa_sigaction = generic_handler; //specifico il gestore del segnale
  act.sa_mask =  set;  //indico i segnali bloccati quando il gestore esegue (tutti bloccati in questo caso)
  act.sa_flags = SA_SIGINFO;
  act.sa_restorer = NULL;  //campo obsoleto
  sigaction(SIGINT,&act,NULL);



  sigprocmask(SIG_BLOCK,&set,NULL); //blocco nuovamente tutti i segnali

  while(1) {
  	sleep(SLEEP_PERIOD);
  	sigpending(&set);
  	if(sigismember(&set,SIGINT)){
  	  sigemptyset(&set); //svuoto la bitmask
  	  sigaddset(&set,SIGINT); //imposto 
  	  sigprocmask(SIG_UNBLOCK,&set,NULL); //sbolocco SIGINT
      /*se un segnale di tipo SIGINT era pendente do la possibilità di eseguire il gestore di tale evento e poi riblocco l'evento*/
  	  sigprocmask(SIG_BLOCK,&set,NULL); //blocco di nuovo la SIGINT
	  }
  }
}
