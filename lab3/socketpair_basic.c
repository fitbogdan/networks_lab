/* socketpair_basic.c - comunicare bidirecțională părinte-fiu printr-o
 * pereche de socket-uri */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    /* ambele capete permit citire ȘI scriere */
    int sv[2];

    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sv) == -1) {
        perror("socketpair");
        return EXIT_FAILURE;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return EXIT_FAILURE;
    }

    char buf[128];
    if (pid == 0) {                     /* fiul folosește sv[1] */
        close(sv[0]);
        ssize_t n = read(sv[1], buf, sizeof buf - 1);
        if (n > 0) {
            buf[n] = '\0';
            printf("[fiu] am primit: %s\n", buf);
            const char *reply = "raspuns de la fiu";
            /* același descriptor, sens invers */
            if (write(sv[1], reply, strlen(reply)) == -1)
                perror("write");
        }
        close(sv[1]);
        exit(EXIT_SUCCESS);
    }

    close(sv[1]);                       /* părintele folosește sv[0] */
    const char *msg = "cerere de la parinte";
    if (write(sv[0], msg, strlen(msg)) == -1)
        perror("write");

    ssize_t n = read(sv[0], buf, sizeof buf - 1);
    if (n > 0) {
        buf[n] = '\0';
        printf("[parinte] am primit: %s\n", buf);
    }
    close(sv[0]);
    wait(NULL);
    return EXIT_SUCCESS;
}
