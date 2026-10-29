/* netio.h - citire/scriere completă și mesaje prefixate cu lungimea
 * Folosit de exemplele din laboratoarele 3-12; se compilează cu -I ../common */
#ifndef NETIO_H
#define NETIO_H

#include <arpa/inet.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

/* Citește exact n octeți. read() pe un pipe sau socket poate întoarce mai puțin
 * decât s-a cerut, deci se reia până la completare.
 * Întoarce n la succes, 0 dacă celălalt capăt a închis, -1 la eroare. */
static inline ssize_t readn(int fd, void *buf, size_t n)
{
    size_t done = 0;
    while (done < n) {
        ssize_t r = read(fd, (char *)buf + done, n - done);
        if (r == 0)
            return 0;                   /* sfârșit de flux (EOF) */
        if (r == -1) {
            if (errno == EINTR)         /* întrerupt de un semnal: se reia */
                continue;
            return -1;
        }
        done += (size_t)r;
    }
    return (ssize_t)n;
}

/* Scrie exact n octeți. Întoarce n la succes, -1 la eroare. */
static inline ssize_t writen(int fd, const void *buf, size_t n)
{
    size_t done = 0;
    while (done < n) {
        ssize_t w = write(fd, (const char *)buf + done, n - done);
        if (w == -1) {
            if (errno == EINTR)
                continue;
            return -1;
        }
        done += (size_t)w;
    }
    return (ssize_t)n;
}

/* Trimite un mesaj: 4 octeți cu lungimea (ordinea rețelei), apoi conținutul. */
static inline int send_msg(int fd, const void *data, size_t len)
{
    uint32_t be = htonl((uint32_t)len);
    if (writen(fd, &be, sizeof be) == -1)
        return -1;
    return writen(fd, data, len) == -1 ? -1 : 0;
}

static inline int send_str(int fd, const char *s)
{
    return send_msg(fd, s, strlen(s));
}

/* Primește un mesaj în buf (cel mult cap-1 octeți) și adaugă terminatorul '\0'.
 * Întoarce lungimea conținutului, -2 dacă celălalt capăt a închis, -1 la
 * eroare. */
static inline ssize_t recv_msg(int fd, char *buf, size_t cap)
{
    uint32_t be;
    ssize_t r = readn(fd, &be, sizeof be);
    if (r <= 0)
        return r == 0 ? -2 : -1;
    uint32_t len = ntohl(be);
    /* nu avem încredere în lungimea anunțată */
    if (len >= cap) {
        errno = EMSGSIZE;
        return -1;
    }
    if (len > 0 && readn(fd, buf, len) <= 0)
        return -1;
    buf[len] = '\0';
    return (ssize_t)len;
}

/* Citește o linie terminată cu '\n' (octet cu octet: simplu, dar ineficient).
 * Întoarce lungimea fără '\n', -2 la închiderea conexiunii, -1 la eroare. */
static inline ssize_t read_line(int fd, char *buf, size_t cap)
{
    size_t len = 0;
    for (;;) {
        char c;
        ssize_t r = read(fd, &c, 1);
        if (r == 0)
            return -2;
        if (r == -1) {
            if (errno == EINTR)
                continue;
            return -1;
        }
        if (c == '\n')
            break;
        if (len + 1 < cap)              /* caracterele în exces sunt ignorate */
            buf[len++] = c;
    }
    buf[len] = '\0';
    return (ssize_t)len;
}

#endif
