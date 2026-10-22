/* ex1_prime.c - Exercițiul 1: dialog părinte-fiu prin două pipe-uri anonime
 * Utilizare: ./ex1_prime <numar> */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

static int is_prime(long n)
{
    if (n < 2)
        return 0;
    for (long d = 2; d * d <= n; d++)
        if (n % d == 0)
            return 0;
    return 1;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Utilizare: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    long n = strtol(argv[1], NULL, 10);

    /* Un pipe este unidirecțional: pentru dialog sunt necesare două. */
    /* req: părinte -> fiu; rsp: fiu -> părinte */
    int req[2], rsp[2];
    if (pipe(req) == -1 || pipe(rsp) == -1) {
        perror("pipe");
        return EXIT_FAILURE;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        /* fiul: citește din req, scrie în rsp */
        close(req[1]);
        close(rsp[0]);

        long value;
        /* Întregul se transmite în reprezentare binară: același calculator,
         * aceeași arhitectură. */
        if (read(req[0], &value, sizeof value) != (ssize_t)sizeof value)
            _exit(1);
        const char *answer = is_prime(value) ? "yes" : "no";
        if (write(rsp[1], answer, strlen(answer)) == -1)
            _exit(1);

        close(req[0]);
        close(rsp[1]);
        _exit(0);
    }

    /* părintele: scrie în req, citește din rsp */
    close(req[0]);
    close(rsp[1]);

    if (write(req[1], &n, sizeof n) == -1)
        perror("write");
    close(req[1]);

    char answer[8] = "";
    ssize_t r = read(rsp[0], answer, sizeof answer - 1);
    if (r > 0)
        printf("%ld este prim? %s\n", n, answer);
    close(rsp[0]);

    wait(NULL);
    return EXIT_SUCCESS;
}
