/*si comporta come server*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>

#define BACKLOG 1
#define SIZE 128
#define ECHO_LENGTH 2


char buff[SIZE];

int comm_sock;

void generic_handler(int signal, siginfo_t *info, void* unused){

        printf("received signal is %d\n",signal);
        /*chiudo il socket di comunicazione, non mi serve più dato che il canale è rotto*/
	close(comm_sock); 
}


int main() {

	int ds_sock;
	struct sockaddr_in my_addr, their_addr;
	int ret;
	unsigned short port = htons(25000);
	int size;
	sigset_t set;
  	struct sigaction act;
	char* IP;
	struct timeval timeout;
	int i;
	int on = 1;

	/*creo un socket con dominio internet, modalità streaming, protocollo di default*/
	ds_sock = socket(AF_INET, SOCK_STREAM, 0);  
	if (ds_sock == -1){
		printf("socket error\n");
		return -1;
	}
	printf("socket installed - descriptor is %d\n",ds_sock);

	/*attivo l'opzione di riusabilità dell'indirizzo di porta 25000*/
	setsockopt(ds_sock,SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)); 

	my_addr.sin_family      = AF_INET;
	my_addr.sin_port        = port;
	my_addr.sin_addr.s_addr = INADDR_ANY; 

	/*associo al nostro socket l'indirizzo contenuto in my_addr*/
	ret = bind(ds_sock,(struct sockaddr*) &my_addr, sizeof(my_addr));
	if(ret == -1){
		printf("bind error\n");
		return -1;
	}
	printf("socket address set up ok\n");

	/*porto il socket in stato listening */ 
	ret = listen(ds_sock, BACKLOG);
	
	if(ret == -1){
		printf("listen error\n");
		return -1;
	}
	printf("socket listen set up ok\n");

	sigemptyset(&set);
	act.sa_sigaction = generic_handler; 
	act.sa_mask =  set;
  	act.sa_flags = SA_SIGINFO;
  	act.sa_restorer = NULL;

  	/*imposto il gestore di segnale SIGPIPE che in sistemi Posix viene generato quando si 
  	 rompe il canale, questo per evitare di andare a leggere/scrivere su canali rotti*/
  	sigaction(SIGPIPE,&act,NULL); 



	new_accept:

	/*accetto una connessione sul listening socket e ottengo l'identificatore del nuovo socket generato 
	 nella variabile globale comm_sock, cioè quella che viene chiusa in caso di ricezione di SIGPIPE */
	comm_sock =  accept(ds_sock,(struct sockaddr*)&their_addr,&size); 
	
	if(comm_sock == -1){
		printf("accept error\n");
		return -1;
	}

#ifdef SOURCE_INFO
	IP = (char*)inet_ntoa(their_addr.sin_addr);
	printf("comm sock is %d - connection source is %s,pn:%u, start logging\n",comm_sock,(char*)IP,their_addr.sin_port);
#endif

#ifdef RECEIVE_TIMEOUT
	timeout.tv_sec = 5;
	timeout.tv_usec = 0;
	/*imposto il receive timeout a 5 secondi e 0 microsecondi solo sul socket di comunicazione (SOL_SOCKET) */
	setsockopt(comm_sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
#endif

#ifdef ALARM
	sigemptyset(&set);
	act.sa_sigaction = generic_handler; 
	act.sa_mask =  set;
  	act.sa_flags = SA_SIGINFO;
  	act.sa_restorer = NULL;
  	sigaction(SIGALRM,&act,NULL);
#endif

	while(1){
#ifdef ALARM
		/*il timeout viene impostato manualmente con gli allarmi, lavorando a livello processo. 
		 Con il receiver timeout invece posso agire sui singoli thread*/
		alarm(5);
#endif
#ifndef PADDING
		/*leggo dal socket usando read() dato che sto lavorando in modalità stream, quando compilo con 
		 RECEIVE_TIMEOUT se entro 5 secondi non arrivano i dati allora il timeout mi sblocca dalla ricezione*/ 
		ret = read(comm_sock,buff,SIZE); 
#else
		/*MSG_WAITALL serve per indicare che il servizio mi deve mantenere in stato di blocco finchè questo non può estrarre 
		 esattamente SIZE_MSG bytes dalla socket,  lo sblocco può avvenire alla ricezione di un segnale o quando arrivano tutti i dati*/
		ret = recv(comm_sock,buff,SIZE,MSG_WAITALL); 
		perror("");
#endif
#ifdef ALARM
		alarm(0);
#endif

		if(ret <= 0){
			break;
		}

		printf("echoing this: ");
		fflush(stdout);
		write(1,buff,ret); /*scrivo in stdout il contenuto del buffer, per una taglia di dati pari a ret byte*/

		/*rispondo al client facendo echo di ciò che ho letto ECHO_LENGHT volte*/
		for (i=0; i< ECHO_LENGTH; i++){
			sleep(1);
#ifndef HANDLE_SIGPIPE
			/*scrivo sulla socket client ret bytes, non curandomi dei residui*/
			ret = write(comm_sock,buff,ret);
#else
			/* MSG_NOSIGNAL: se il canale è rotto il segnale SIGPIPE lo voglio ignorare, accorgendomi dell'errore guardando il codice di ritorno della send() */
			ret = send(comm_sock,buff,ret,MSG_NOSIGNAL);
#endif
		}
	}
	close(comm_sock);

	printf("connection closed - accepting a new one\n");

	fflush(stdout);
	/*mi riporto in stato di accept di una nuova connessione riniziando il ciclo*/
	goto new_accept;

	return 0;
}
