/*si comporta come client*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

int ds_sock;

void * get_echo(){
	char buff[128];
	while(1){
		write(1,buff,read(ds_sock,buff, 128));
	}
}

char buff[128];

int main() {

	struct sockaddr_in my_addr, their_addr;
	int ret;
	unsigned short port = htons(25000);
	int comm_sock;
	pthread_t thread;

	ds_sock = socket(AF_INET, SOCK_STREAM, 0); /*creo il socket client*/
	if (ds_sock == -1){
		printf("socket error\n");
		return -1;
	}
	printf("socket installed - descriptor is %d\n",ds_sock);

	memset(&their_addr, 0, sizeof(their_addr));
	my_addr.sin_family      = AF_INET;
	my_addr.sin_port        = htons(0);
	inet_aton("127.0.0.1",&my_addr.sin_addr);

	/*associo al mio socket l'indirizzo contenuto in my_addr*/
	ret = bind(ds_sock, (struct sockaddr*)&my_addr, sizeof(my_addr));
	
	if(ret == -1){
		printf("bind error\n");
		return -1;
	}

	memset(&their_addr, 0, sizeof(their_addr));
	their_addr.sin_family      = AF_INET;
	their_addr.sin_port        = port;

	/*l'indirizzo dell'host server è 127.0.0.1, 
	 inet_aton trasforma l'indirizzo IP (formato stringa) nella sua rappresentazione in byte*/
	inet_aton("127.0.0.1",&their_addr.sin_addr); 

	ret = connect(ds_sock,(struct sockaddr*) &their_addr, sizeof(their_addr));
	if(ret == -1){
		printf("connect error\n");
		return -1;
	}
	printf("socket connection set up ok\n");

	/*creo un thread che leggera l'echo del server*/
	pthread_create(&thread,NULL, get_echo,NULL);

	/*leggo dal server e scrivo in buff, i residui non vengono gestiti*/
	while(1){	
	  ret = read(0,buff, 128);
	  write(ds_sock,buff,ret);
	}

	return 0;
}
