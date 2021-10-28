#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[]) {

  int fd;
  int ret;

  if (argc!= 2) {
    printf("Syntax: write_on_fifo <fifo_name>\n"); //passo il nome della fifo al main
    exit(-1);
  }

  ret = mkfifo(argv[1], S_IRUSR|S_IWUSR); //create a named pipe

  if (ret == -1) {
    perror("fifo creation error: \n");
    exit(EXIT_FAILURE);
  }

  fd = open(argv[1], O_WRONLY); //apro la ipe solo in scrittura con il thread main
  // dato che è una operazione bloccante, finchè non avrò almeno un processo lettore che apre la pipe creata non potrò iniziare a scrivere
  // chiudendo il processo lettore, se provo a scrivere nuovamente con il processo scrivente avrò un sigfault

  if (fd == -1) {
    perror("fifo open error: \n");
    exit(EXIT_FAILURE);
  }

  printf("fd=%d\n",fd);
  fflush(stdout);
  close(1); //chiudo lo stdoutput
  dup(fd); //duplico il canale che avevo aperto sulla pipe
  execve("./writer", NULL, NULL); //il processo chiamato scriverà quindi sulla pipe e non sullo stdoutput perchè eredita le informazioni di ambiente dal padre
  perror("Exec error: "); //se non riesco ad eseguire la execve()
  exit(EXIT_FAILURE);
}

