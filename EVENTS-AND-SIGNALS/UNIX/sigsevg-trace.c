#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

char v[1024];

//con questo meccanismo sopravvivo al segmentation fault
void generic_handler(int signal, siginfo_t *info, void* unused){

  sigset_t set;

	printf("received signal is %d - address is %p\n",signal,info->si_addr);
  // in si_addr ci sarà l'indirizzo che ha causato il segfault
	sleep(1);
}


int main(int argc, char **argv){

  int  i;
  char c;
  sigset_t set;
  struct sigaction act;
  char* addr = (char*)0xffffff00;  //scelgo una zona di memoria dove puntare, tipicamente non utilizzato da un'applicazione di questo tipo 


  sigfillset(&set);
  sigdelset(&set,SIGSEGV);
  sigdelset(&set,SIGINT);
  //ho bloccato tutti i segnali tranne SIGINT e SIGSEGV

  act.sa_sigaction = generic_handler; 
  act.sa_mask =  set;
  act.sa_flags = SA_SIGINFO;
  act.sa_restorer = NULL;
  sigaction(SIGSEGV,&act,NULL); //imposto la gestione di SIGSEGV


  while(1) {

  	sleep(5);
    /*l'istruzione macchina che ha causato il segfault non è stata committata, figura come non eseguita
     quando riprenderemo il controllo lo rifaremo esattamente nell'istruzione che lo ha causato, se non ho 
     mappato nel gestore quell'indirizzo di memoria per riparare al segfault andro nuovamente in errore */ 
  	c = *addr;  //probabilmente causerà segmentation fault, che verrà intercettato dall'handler
  }
}
