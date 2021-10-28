#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

#ifndef NUM_THREADS
#define NUM_THREADS 1
#endif

#define MAX_STRING_LEN     (4096 << 1) 

#ifndef NUM_TARGET_STRINGS
#define NUM_TARGET_STRINGS 1
#endif

char* the_strings[NUM_TARGET_STRINGS] ; //archivio globale di stringhe

//__thread per dichiarare variabili TLS

__thread char buffer[MAX_STRING_LEN];    // ogni thread ha il suo buffer
__thread int occurrences = 0;            // ogni thread ha la sua variabile di occorrenze

void * SearchThread(){

  int status;
  int i;

  while(scanf("%s",buffer) == 1){
	for(i=0;i<NUM_TARGET_STRINGS;i++){
		if(strstr(buffer,the_strings[i]) != NULL){  //trova la prima occorrenza di the_string[i] in buffer
			occurrences++;
		}
	}
  }	
  printf("found %d occurrences of searched strings\n",occurrences);
  status = 0;
  pthread_exit((void *)&status);
} 

int main (int a, char **b )
{
  int i;
  pthread_t tid[NUM_THREADS];
  long thread_count = 0;

  if (a != 2){
    printf("usage: prog_name num_threads\n");
    return 1;
  }

  thread_count = strtol(b[1], NULL, 10);
  printf("running with %ld threads\n", thread_count);
 
  for(i=0; i<NUM_TARGET_STRINGS; i++){
	buffer[0] = '\0';
	scanf("%s",buffer);
	the_strings[i] = strdup(buffer);  //duplico la stringa acquisita in buffer
        if (the_strings[i] == NULL) exit(-1);
  }

  for(i=0; i<NUM_THREADS; i++){
	pthread_create(&tid[i],NULL,SearchThread,NULL);
  }
  for(i=0; i<NUM_THREADS; i++){
	pthread_join(tid[i],NULL);  //attendo la terminazione
  }
  exit(0);
}

