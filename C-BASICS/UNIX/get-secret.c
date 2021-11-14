#include <stdio.h>

char format_line[4096];

char *secret = "francesco";

unsigned long x = 0x4006b4; 

int main(int a, char** b){

	printf("secret is at %p\n",secret);

	while(1)
	{
		scanf("%s",format_line);  	//inserendo come format line %s dovrebbe stampare la stringa contenuta all'indirizzo x 
									//che in teoria è l'indirizzo dell'array secret ma in pratica no perchè l'address space viene randomizzato
		printf(format_line,x);
		printf("\n");

	}
}
