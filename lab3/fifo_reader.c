/* fifo_reader.c - afișează datele primite printr-un FIFO de la un proces
 * neînrudit */
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_PATH "/tmp/lab3_fifo"

int main(void)
{
    if (mkfifo(FIFO_PATH, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo");
        return 1;
    }

    /* se blochează până apare un scriitor */
    int fd = open(FIFO_PATH, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    char buf[256];
    ssize_t n;
    while ((n = read(fd, buf, sizeof buf)) > 0)
        if (write(STDOUT_FILENO, buf, (size_t)n) == -1)
            break;

    close(fd);
    /* FIFO-ul persistă pe disc până la ștergerea explicită */
    unlink(FIFO_PATH);
    return 0;
}
