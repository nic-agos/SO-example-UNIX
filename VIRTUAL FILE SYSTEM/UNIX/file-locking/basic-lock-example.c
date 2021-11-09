
#include <sys/fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s file\n", argv[0]);
        exit(1);
    }

    int fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    // vogliamo attuare una gestione specifica sul 
    struct flock fl = {};
    fl.l_type = F_WRLCK;  //se qualcuno vuole leggere può operare in concorrenza sul file 
    fl.l_whence = SEEK_SET;  
    fl.l_start = 0;
    fl.l_len = 0; //quale parte del file voglio dare il lock, in questo caso tutto il file (default = 0)

    if (fcntl(fd, F_SETLKW, &fl) == -1) {  
        perror("fcntl");
        exit(1);
    }

    while(1);
    exit(0);
}

