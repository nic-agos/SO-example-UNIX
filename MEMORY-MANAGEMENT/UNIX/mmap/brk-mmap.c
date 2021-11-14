// moves brk by INCREMENT - possibly also tries to mmap one page on the new brk
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

#define PAGE_SIZE 4096

int INCREMENT=0;

char v[4096];
char c;


extern char _edata; // end of initialized data section
extern char _end; // end of non initialized data section


int main(int argc, char** argv){
  void*addr, *oldboundary;
  char c;
  int i;

  if(argc < 2) {
    printf("usage: prog memory-increment [mmap]\n");  //mmap argomento opzionale
    exit(-1);
  }
  printf("edata is %10p\n",&_edata);
  printf("end is %10p\n",&_end);

  addr = oldboundary = (void*)sbrk(0); //per ottenere il valore di brk corrente
  printf("old program boundary is at address %x (boundary page number is %d)\n",(unsigned)addr, (unsigned)addr/(unsigned)PAGE_SIZE);

  INCREMENT =  atoi(argv[1]);  //atoi trasforma da formato stringa a formato numerico l'incremento passato come input al programma
  sbrk(INCREMENT);  //incremento il brk

  addr = (void*)sbrk(0);
  printf("new program boundary is at address %x (boundary page number is %d)\n",(unsigned)addr, (unsigned)addr/(unsigned)PAGE_SIZE);

  if(argv[2] && (strcmp(argv[2],"mmap")==0)) {
    /*mappo una pagina successiva al brk corrente, mmap arrotonda l'indirizzo di partenza 
    per il mapping (addr in questo caso) al boundary iniziale di una pagina */
    
    mmap(addr,PAGE_SIZE,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS|MAP_FIXED,0,0); 
  }
  
  for(i=0;;i++){ // eventually SEGFAULT
    printf("cycle %d accessing address %x\n",i,(unsigned)(oldboundary+i));  //mi spiazzo a partire dal vecchio brk
    c = *(char*)(oldboundary+i);  //provo ad eseguire una loaddi un valore ad uno specifico indirizzo di memoria
  }
}




