#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

// compile with gcc threads-performance.c -lpthread
// use with time ./a.out processes or time ./a.out threads
#define SPAWNS 5

void* child_thread(void*p){

}

int main(int argc, char** argv){

	int i;
   int status;
   void **thread_status;
   pthread_t tid;

   if (argv[1]==NULL){
	printf("missing arg[1]\n");
	exit(-1);
   }
  
   if (strcmp("processes", argv[1]) == 0) {
		for (i=0;i<SPAWNS;i++){
	          if(fork()) wait(&status);
		  else exit(0);		
		}
   }

   if (strcmp("threads", argv[1]) == 0) {
		for (i=0;i<SPAWNS;i++){
		  pthread_create(&tid,NULL,child_thread,NULL);
		  pthread_join(tid,thread_status);
		}
	}
}
