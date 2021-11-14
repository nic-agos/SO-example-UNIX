#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE (100000)

long v[SIZE] = {[0 ... (SIZE-1)] -1};

long counter = 0;  // variabile di controllo

void * producer(void* dummy){

	long data = 0;
	long my_index = 0;

	printf("ready to produce\n");

retry:
	while(counter < SIZE){  // entro nel while solo se ci sono slot liberi nell'array
		v[my_index] = data;  // nella posizione 
		my_index = (my_index+1)%SIZE;  // la struttura dati comune è gestita come array circolare
		data++;
		counter++;
	
	}
	goto retry;


}

void * consumer(void* dummy){

	long data = 0;
	long my_index = 0;
	long value;

	printf("ready to consume\n");

retry:
	while(counter > 0){  // entro nel while se ci sono dati da leggere
		value = v[my_index];
		printf("got value %d\n",value);
		if(value != data){  // data è il valore che mi aspetto
			printf("consumer: synch protocol broken at expected value: %d - real is %d!!\n",data,value);
			exit(-1);

		};
		data++ ;
		my_index = (my_index+1)%SIZE;
		counter--;
	
	}
	goto retry;

}

int main(int argc, char** argv){

	pthread_t prod, cons;

	pthread_create(&cons,NULL,consumer,NULL);   /*creo il thread consumer*/
	sleep(1);
	pthread_create(&prod,NULL,producer,NULL);	/*creo il thread consumer*/

	pause();  // attendo i figlio

}

