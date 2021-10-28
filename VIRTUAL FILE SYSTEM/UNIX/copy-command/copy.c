#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 1024

int main(int argc, char *argv[]) { 
	int sd, dd, size, result; 
	char buffer[BUFSIZE];

	 if (argc != 3) { /* check the number of arguments */ 

		printf("usage: copy source target\n");
		exit(1);
	 }  

	 /* read only opening of the source file */
	 sd=open(argv[1],O_RDONLY); 
	 if (sd == -1) {  /*se non ho capability di lettura su tale file la syscall fallisce e ritorna -1*/
		printf("source file open error\n");
	        exit(1);
	 }  

	 /* destination file creation */
	 /*0660 signifa read and write per l'user e read and write per il gruppo*/
	 dd=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0660); /*se il file non esiste lo copio, se esiste ed ha già un conenuto devo troncarlo*/
	 if (dd == -1) {
		printf("destination file creation error\n");
	        exit(1);
	 }


	/* let's start with the copy operations */
	/*leggo a blocchi di BUFSIZE dal file sorgente e li scrivo sul nuovo file*/
	do { 
	      	 /* read up to BUFSIZE from source */
          	size=read(sd,buffer,BUFSIZE);
	        if (size == -1) {
	          printf("source file read error\n"); 
	          exit(1);          	

		}	

	 	/* write up to BUFSIZE to destination file */ 
	 	/*scrivo size byte ogni volta, cioè la quantità di byte che effettivamente vengono letti*/
		result = write(dd,buffer,size);          	
		if (result == -1) {
             	printf("destination file write error\n");
	        	exit(1);
        }
	} while(size > 0);

    close(sd);
	close(dd);

  }/* end main*/

