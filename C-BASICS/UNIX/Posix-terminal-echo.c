#include <unistd.h>

// utilizzo direttamente le syscall posix invece delle funzioni di libreria
int main(int x, char** y){
	char c;

	while(1){
		read(0,&c,1);          // sorgente/destinazione delle informazioni: 0 canale standard dell'input, area di memoria coinvolta, quantità di byte coinvolta
		write(1,&c,1);         // 1 canale standard dell'input, area di memoria coinvolta, quantità di byte coinvolta

	}
}
