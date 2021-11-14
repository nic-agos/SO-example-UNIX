#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>

#define PAGE_SIZE (4096) 

#define NUM_TARGET_PAGES 50000

/* dichiaro un array di 4096x50000 byte, v è una variabile globale ed è ospitato all'interno di diverse pagine, 
 specificando l'attributo aligned(4096) gli diciamo che l'indirzzo dell'array deve coincidere con l'inizio di 
 una pagina quindi occuperà esattamente 50000 pagine */

char v[PAGE_SIZE*NUM_TARGET_PAGES] __attribute__((aligned(4096)));  

int main(int argc, char** arv){
        
	int i;
	char* buffer;

	buffer = (char*)mmap(NULL,PAGE_SIZE*NUM_TARGET_PAGES,PROT_READ|PROT_WRITE,MAP_ANONYMOUS|MAP_PRIVATE,0,0);

 	buffer = v;  /*ci dimentichiamo quale è l'indirizzo della pagine che abbiamo mappato, puntando ad altre pagine*/

#ifndef SAME_PAGE_WRITE  
	/*scrivo all'inizio di ogni pagina il carattere f*/
	for (i=0;i<NUM_TARGET_PAGES;i++){
		buffer[i*PAGE_SIZE] = 'f';
	}
#else
	/*scrivo il carattere f nella posizione 0 del buffer per 50000 volte*/
	for (i=0;i<NUM_TARGET_PAGES;i++){
		buffer[0] = 'f';  
	}
#endif


}
