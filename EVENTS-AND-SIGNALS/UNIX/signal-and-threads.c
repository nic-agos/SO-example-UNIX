#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>


void printA(){
	printf("A\n");
}

void printB(){
	printf("B\n");
}

/* i due thread in concorrenza vogliono catturare lo stesso evento (SIGINT), solo uno dei due a 
 regime verrà utilizzato, l'ultimo che è stato impostato*/
void *generic_threadA(){
	signal(SIGINT,printA);
	while(1) {
		pause();
		printf("I'm thread A\n");
	}
}

void *generic_threadB(){
	signal(SIGINT,printB);
	while(1) {
		pause();
		printf("I'm thread B\n");
	}
}



int main(int argc, char **argv){

  pthread_t thread;
  pthread_attr_t attr;

  pthread_create(&thread, NULL, generic_threadA, NULL);
  pthread_create(&thread, NULL, generic_threadB, NULL);


  while(1) {
	pause();  //lo sblocco avviene solo in caso di una segnalazione che il thread main riceve
	printf("I'm thread main\n"); 
  }

}
