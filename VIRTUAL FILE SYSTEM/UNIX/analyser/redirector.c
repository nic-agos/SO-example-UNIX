#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[]) {

  int fd;

  if (argc!= 2) {
    printf("Syntax: write_on_file <file_name>\n");
    exit(-1);
  }

  /*apro il file specificato in argv[1]*/
  fd=open(argv[1], O_CREAT| O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR);
  /*fd è un canale di I/O che mi porta al file*/

  if (fd== -1) {
    perror("Open error: ");
    exit(-2);
  }

  printf("fd=%d\n",fd);
  close (1); /*chiudo stdout*/
  /*duplico il canale aperto sul file nella entry 1 dei canali aperti,
    qualsiasi cosa scritta da tastiera finirà nel file*/
  dup(fd); 
  execve("./writer", NULL, NULL);
  perror("Exec error: ");
  exit(-3);
}

