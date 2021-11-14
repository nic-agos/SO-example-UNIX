#include <unistd.h>

#define MAXBUF 4096

int main () {
	char buffer[MAXBUF];
	int res_r,res_w,prev_w;

	res_r = read(0, buffer, MAXBUF);  /*dati letti*/ 
	/*non controllo se la read() ritorna -1*/

	while(res_r) {
		/*non è detto che mi basti una sola write per scrivere tutti i dati che ho letto quindi eseguo un ciclo per farlo*/
		prev_w = 0; /*dati scritti in precedenza*/
		res_w = 0; /*dati rimanenti da scrivere*/
		do {
			prev_w =prev_w +res_w;
			res_w = write(1, &buffer[prev_w],res_r - prev_w);
		} while (res_w+prev_w <res_r);

 		res_r=read(0, buffer, MAXBUF); /*leggo dallo stdin*/
	}

 	return 0;

}
