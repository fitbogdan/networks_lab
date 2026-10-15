/* sig_handler.c - tratarea semnalelor cu sigaction()
* Test: ./sig_handler & ; kill -USR1 <pid> ; kill -INT <pid> ; kill
* -TERM <pid> */
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
/* Singurul tip pe care un handler îl poate modifica în siguranță. */
static volatile sig_atomic_t got_usr1, got_int, done;
static void handler(int sig)
{
/* În handler se apelează doar funcții async-signal-safe (vezi
* signal-safety(7)). printf() NU este sigură; aici doar notăm
* evenimentul. */
if (sig == SIGUSR1)
got_usr1 = 1;
else if (sig == SIGINT)
got_int = 1;
else if (sig == SIGTERM)
done = 1;
}
int main(void)
{
struct sigaction sa;
memset(&sa, 0, sizeof sa);
sa.sa_handler = handler;
/* semnale blocate suplimentar pe durata handlerului */
sigemptyset(&sa.sa_mask);
/* reia automat apelurile de sistem întrerupte */
sa.sa_flags = SA_RESTART;

if (sigaction(SIGUSR1, &sa, NULL) == -1 ||
sigaction(SIGINT, &sa, NULL) == -1 ||
sigaction(SIGTERM, &sa, NULL) == -1) {
perror("sigaction");
return 1;
}
printf("PID %d: astept SIGUSR1, SIGINT, SIGTERM\n", getpid());
while (!done) {
/* suspendă procesul până la sosirea unui semnal */
pause();
if (got_usr1) {
got_usr1 = 0;
printf("am primit SIGUSR1\n");
}
if (got_int) {
got_int = 0;
printf("am primit SIGINT; nu ma opresc\n");
}
}
printf("am primit SIGTERM; terminare ordonata\n");
return 0;
}