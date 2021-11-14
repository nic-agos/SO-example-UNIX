#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "mini-tar.h"

int descriptors[MAX_MANAGEABLE_FILES];

header tar_head;

int main(int argc, char *argv[]) { 
	int dd, size, result; 
	char buffer[BUFSIZE];
	int i;
	off_t seek;

	if (argc < 3) { /* check the number of arguments */ 

		printf("usage: mini-tar dest source_1 [source_2] .. [source_n]\n");
		exit(EXIT_FAILURE);
	}  


	/* destination file creation */
	dd=open(argv[1],O_WRONLY|O_CREAT|O_TRUNC,0660); 
	if (dd == -1) {
		printf("destination file creation error\n");
	    exit(EXIT_FAILURE);
	}

	// scorro i file che voglio unire per compilare l'header
	for (i=2;argv[i]!=NULL;i++){

	  	tar_head.num_files++;

		if(strlen(argv[i])>=MAX_FILE_NAME_LENGTH){
			printf("File %s - name too long\n",argv[i]);
	    	return EXIT_FAILURE;
		}	

	  	descriptors[i-2] = open(argv[i],O_RDONLY); //tento di aprire il file salvandomi il descrittore associato in un array
	  	if(descriptors[i-2] == -1){
	    	printf("Cannot access file %s\n",argv[i]);
	    	return EXIT_FAILURE;
        }

	  	printf("file %s correctly opened - access descriptor is %d\n",argv[i],descriptors[i-2]);

	  	memcpy(&(tar_head.file_names[i-2]),argv[i],strlen(argv[i])+1);  //scrivo il nome del file nell'header

	}	

	//stampa le informazioni presenti nell'header compilato
	printf("Tar head audit - num files %d - file names:\n",tar_head.num_files);
        for(i=0;i<tar_head.num_files;i++){
		printf("%s\n",tar_head.file_names[i]);
		fflush(stdout);
	}	


	// scrivo sul file l'header 
	result = write(dd,&tar_head,sizeof(header));          	

	printf("tar header size is %d - fseek is %d\n",sizeof(header),result);
	fflush(stdout);

	for(i=0;i<argc-2;i++){
		printf("taring file %s\n",argv[i+2]);
		fflush(stdout);

		seek = lseek(dd,0,SEEK_CUR); // il seek viene posizionato nella prima locazione dopo l'header

		tar_head.start_position[i] = seek; //aggiorno la start position nell'header per il file i-esimo in memoria (non sul file)

		printf("start position is %d\n",seek);
		fflush(stdout);

		/* let's start with the copy operations */
		do { 
			AUDIT
			printf("cycling - descriptor is %d\n",descriptors[i]);
		      	 /* read up to BUFSIZE from source */
       		   	size=read(descriptors[i],buffer,BUFSIZE); //leggo ogni volta al massimo BUFSIZE byte dal file
		        if (size == -1) {
		        	printf("file read error\n"); 
			  		fflush(stdout);
		          	exit(EXIT_FAILURE);          	

			}	
			AUDIT
			printf("read done\n");
			fflush(stdout);

	 		/* write up to BUFSIZE to destination file */ 
			result = write(dd,buffer,size);          	
			if (result == -1) {
         		printf("mini-tar file write error\n");
		  		fflush(stdout);
       		 	exit(EXIT_FAILURE);
            }

		} while(size > 0);

		seek = lseek(dd,0,SEEK_CUR);

		tar_head.end_position[i] = seek;  //aggiorno la end position nell'header per il file i-esimo in memoria (non sul file)


		printf("end position is %d\n",seek);
		fflush(stdout);
			
	}

	printf("realigning the header\n");
	fflush(stdout);

	lseek(dd,0,SEEK_SET);

	result = write(dd,&tar_head,sizeof(header)); //sto scrivendo byte, per estrarli          	

  }/* end main*/

