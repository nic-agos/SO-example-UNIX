#include <unistd.h>
#include <stdlib.h>

// use ./a.out & to run in background the program
// use ps to list all process in execution on that shell

#define NUM_FORKS 10

int main(int a, char ** b){

	int residual_forks = NUM_FORKS;

	for(;residual_forks > 0 ; residual_forks--){
		if(fork()>0){
				continue;
		}
		else{
			break;
		}
	

	}
	pause();



}
