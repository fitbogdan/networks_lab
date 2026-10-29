#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "netio.h"

#define PORT 2024

int main(void){

    struct sockaddr_in server;
    struct sockaddr_in from;
    char msg[100];
    char msgrasp[100]="";

    int sd;
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("[server] Eroare la creare socket");
        return errno;
    }

    memset(&server, 0, sizeof(server));
    memset(&from, 0, sizeof(from));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    server.sin_port = htons(PORT);

    if (bind (sd, (struct sockaddr *) &server, sizeof (struct sockaddr)) == -1){
        perror ("[server]Eroare la bind().\n");
        return errno;
    }


    if(listen(sd,5) == -1){
        perror("[server]Eroare la listen().\n");
        return errno;
    }
    unsigned int next_id = 1;

    while(1){
        int client;
        int length = sizeof(from);

        printf("[server]Asteptam la portul %d\n",PORT);
        fflush(stdout);

        client = accept(sd, (struct sockaddr *)&from, &length);

        if(client < 0){
            perror("[server]Eroare la accept()\n");
            continue;
        }

        memset(msg, 0, sizeof(msg));
        printf("[server]Astept msj\n");
        fflush(stdout);


        // if(read(client,msg,sizeof(msg)) <= 0){
        //     perror("[server]Eroare la read() de la client.\n");
        //     close(client);
        //     continue;
        // }


        
        unsigned int id = next_id++;
        int x;
        if(readn(client,&x,sizeof(x)) == sizeof(x)){
            int value = ntohl(x);

            printf("[server] clientul: id=%u, %d -> %d\n",id,value,value+1);
            int reply[2] = {htonl(value+1), htonl(id)};

            if(writen(client,reply,sizeof(reply)) == -1){
                perror("[server] erorare la write catre client\n");
            }
        }
        else{
            fprintf(stderr, "[server] clientul %u nu am trimit 4 bytes\n", id);
        }


        close(client);
    }
}