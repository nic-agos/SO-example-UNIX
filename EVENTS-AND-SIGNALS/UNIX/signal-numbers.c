#include <stdio.h>
#include <signal.h>
#include <unistd.h>


void generic_handler(int signal){  //passiamo anche il codice numerico dell'evento verificatosi

	printf("received signal is %d\n",signal);
}



int main(int argc, char **argv){

  int  i;

  //utilizzo lo stesso gestore per 3 diversi segnali
  signal(SIGINT,generic_handler);
  signal(SIGUSR1,generic_handler);
  signal(SIGUSR2,generic_handler);

  while(1) {
	  pause();
  }

}
