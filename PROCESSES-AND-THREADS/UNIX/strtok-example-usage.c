#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// to compile with ifdef use -DSEGAFAULT_TEST
/*
char * strtok ( char * str, const char * delimiters );
A sequence of calls to this function split str into tokens, which are sequences 
of contiguous characters separated by any of the characters that are part of delimiters.

On a first call, the function expects a C string as argument for str, whose first 
character is used as the starting location to scan for tokens. In subsequent calls, 
the function expects a null pointer and uses the position right after the end of 
the last token as the new starting location for scanning.
*/

// use -fsyntax-only to suppress gets() warnings

#define MAX_TOKENS 128

// dichiaro il prototipo perchè gets è deprecata per motivi di sicurezza
int gets(char*); //il uso separatore è /n

char line[4096];

char* s = " ";	//blank is used as the tokenizer character (carattere di delimitazione)

#ifdef SEGAFAULT_TEST
char * pointer = "ciao a tutti";  //pointer sarà salvato in DATA che è una zona read only quindi quando ci chiamo una funzione va in seg fault
#endif

int main(int argc, char** argv) {
	char **token_vector;  //ci posso registrare un indirizzo di un array di puntatori a carattere
      	char* p;
      	char* tokens[MAX_TOKENS];
      	int i;

	gets(line);		//prende in input una stringa inserita da terminale
	p = (char*)strtok(line,s);	//tokenize and get the pointer to the first token

#ifdef SEGAFAULT_TEST
	// sto eseguendo una seconda tokenizzazione e dato che il primo parametro non è null allora la chiamata prima viene invalidata
	p = (char*)strtok(pointer,s);	//you should never try to do this
#endif

	i = 0;
	tokens[i] = p;

	while(p){		//get the pointers to the other tokens
	  	p = (char*)strtok(NULL,s);
		tokens[++i] = p;
		
	} 
	tokens[++i] = NULL;  //serve per identificare la fine dell'array

	token_vector = tokens;

	while(*token_vector){	//audit the tokens on the standard output
		printf("%s\n",*token_vector);
		token_vector++;

	}
}
