#include <stdio.h>

char format_line[4096];            		// 4096 byte disponibili in memoria inidicati con il nome format_line dove inserire
										// tipi di formato (%p, %s, ...)
unsigned long x = 32; 

int main(int a, char** b){

	while(1)
	{
		scanf("%s",format_line);	 // se inserisco %s da shell come input ho segmentation fault perchè printf scorre tutta l'area di 
		printf(format_line,x);		 // format_line cercando una stringa e quindi \0, non vuol dire che magari non sono stati 
		printf("\n");			     // trovati caratteri in memoria ma che sono stati emessi senza essere stai flushati dal
		                             // buffer di output, finendo poi in una zona non più valida del contenitore di memoria.
									 // se come imput inserisco 

	}
}
