#include <unistd.h>
#include <stdio.h>

extern char** environ;  //mantiene il riferimento ad un array di puntatori a stringhe, le informazioni vengono fornite dalle librerie

void main(int argc, char **argv){
   	 char ** addr=environ;

         printf("process %d - environ head pointer is at address: %u\n",getpid(),(unsigned long)environ);
	 fflush(stdout);
	 
	 while(*addr){
      	      printf("%s\n",*(addr));
	      fflush(stdout);
 	      addr++;
	}

// passando argv[0] se ho invocato da shell questo programma allora vuol dire che gli passero il nome stesso della shell
//       execve(argv[0],argv,NULL);  // rilanancia se stesso in maniera iterativa con ambiente nullo 
//       execve(argv[0],argv,environ);
//        execve(argv[0],NULL,NULL);
//        execve("ls",NULL,environ);
//	printf("execve failed\n");
//	fflush(stdout);
}


