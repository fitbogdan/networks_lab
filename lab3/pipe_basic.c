/* pipe_basic.c - canal anonim între părinte și fiu */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    int fds[2];                         /* fds[0] = citire, fds[1] = scriere */
    int pipecp[2];

    /* canalul se creează ÎNAINTE de fork() */
    if (pipe(fds) == -1) {
        perror("pipe");
        return EXIT_FAILURE;
    }
    if(pipe(pipecp) == -1){
        perror("pipe");
        return EXIT_FAILURE;
    }



    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {                     /* fiul citește */
        /* închide capătul nefolosit: altfel nu ar primi niciodată EOF */
        close(fds[1]);
        close(pipecp[0]);
        char buf[64];
        ssize_t n;
        /* 0 = toți scriitorii au închis */
        while ((n = read(fds[0], buf, sizeof buf)) > 0)
            printf("[fiu] am citit %zd octeti: %.*s\n", n, (int)n, buf);
        close(fds[0]);


        const char *msg = "salut de la fiu, prin pipe";
        if (write(pipecp[1], msg, strlen(msg)) == -1)
            perror("write");

        printf("[fiu]: am trimis msj\n");
        close(pipecp[1]);

        exit(EXIT_SUCCESS);
    }

    /* părintele scrie: închide capătul de citire */
    close(fds[0]);
    close(pipecp[1]);
    const char *msg = "salut prin pipe";
    if (write(fds[1], msg, strlen(msg)) == -1)
        perror("write");
    close(fds[1]);                      /* închiderea produce EOF la cititor */



    char buf[64];
    ssize_t n;
    /* 0 = toți scriitorii au închis */
    while ((n = read(pipecp[0], buf, sizeof buf)) > 0)
        printf("[tatal] am citit %zd octeti: %.*s\n", n, (int)n, buf);
    close(pipecp[0]);

    wait(NULL);
    return EXIT_SUCCESS;
}
