#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>

#define PAGE_SIZE (4096) 

#define NUM_TARGET_PAGES 10 

int main(int argc, char** arv){
        
	char* buffer;  
        
	/*voglio utilizzare più memoria di quella che attualmente è lecito utilizzare 
	sceglie il sistema operativo dove mappare la memoria, mappo 4096x10 byte, 
	MAP_ANONYMOUS quindi la memoria è inizializzata tutta a zero, MAP_PRIVATE quindi i child non possono utilizzarla*/

	buffer = (char*)mmap(NULL, PAGE_SIZE*NUM_TARGET_PAGES, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, 0, 0);  
	if (buffer == NULL){
		printf("mmap error\n");
		return -1;
	}

	return 0;

}
