/* fifo_writer.c - scrie liniile citite de la tastatură într-un FIFO
 * Rulare: într-un terminal ./fifo_reader, în altul ./fifo_writer */
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_PATH "/tmp/lab3_fifo"

int main(void)
{
    /* FIFO-ul este o intrare în sistemul de fișiere; EEXIST nu este o eroare
     * aici. */
    if (mkfifo(FIFO_PATH, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo");
        return 1;
    }

    /* open(O_WRONLY) se blochează până când un alt proces deschide FIFO-ul
     * pentru citire. */
    int fd = open(FIFO_PATH, O_WRONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof line, stdin) != NULL) {
        /* EPIPE/SIGPIPE dacă cititorul a dispărut */
        if (write(fd, line, strlen(line)) == -1) {
            perror("write");
            break;
        }
    }
    close(fd);                          /* cititorul primește EOF */
    return 0;
}
