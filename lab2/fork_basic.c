/* fork_basic.c - crearea unui proces fiu și preluarea codului său de
* terminare */
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
int main(void)
{
    /* după fork(), fiecare proces are propria copie */
    int x = 10;
    pid_t pid = fork();

    if (pid == -1) { /* eroare: nu s-a creat niciun proces */
        perror("fork");
        return EXIT_FAILURE;
    }


    if (pid == 0) { /* ramura executată DOAR de fiu */
        x += 5;
        printf("[fiu] PID=%d PPID=%d x=%d\n", getpid(), getppid(), x);
        exit(7); /* codul de terminare: 0..255 */
    }



    /* ramura executată DOAR de părinte; pid = PID-ul fiului */
    int status;
    if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid");
        return EXIT_FAILURE;
    }
    printf("[parinte] PID=%d fiu=%d x=%d\n", getpid(), pid, x);
    /* terminare normală: exit() sau return din main */
    if (WIFEXITED(status))
        printf("[parinte] fiul s-a terminat cu codul %d\n",


    WEXITSTATUS(status));
    else if (WIFSIGNALED(status)) /* terminare cauzată de un semnal */
        printf("[parinte] fiul a fost terminat de semnalul %d\n",


    WTERMSIG(status));
    return EXIT_SUCCESS;
}