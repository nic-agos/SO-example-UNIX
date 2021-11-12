#include <stdio.h>
#include <fcntl.h>
#include <signal.h>

#define timeout 3

unsigned int a,b,c,d,e,f;

void printdata(int sgnumber){
	printf("values are %d - %d - %d -%d -%d - %d \n",a,b,c,d,e,f);
}

int main (int argc, char**argv){

	unsigned int i = 0;
	signal(SIGINT, printdata); /*stiamo cercando di gestire il segnale emanato da ctrl+C*/ 

	while (1){
		/*non uso syscall quindi non chiamo il kernel ma lavoro in user space*/
		/*non è un'istruzione atomica ma un blocco di istruzioni quindi potrebbe succedere che non riesco ad eseguire 
		 tutte le operazioni prima dell'avvenimento di un evento quindi le variabili potrebbero avere valori differenti*/
		a = b = c = d = e = f = (++i)%1024;
	}	

	/*per uscire da questa applicazione uso ctrl+\*/ 
}
