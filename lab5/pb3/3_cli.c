#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include<sys/socket.h>
#include "netio.h"


int main(int argc, char* argv[]){

    int sd = 0;
    if((sd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("[client] Socket");
        return -1;
    }

    struct sockaddr_in server;
    unsigned int port = atoi(argv[2]);
    server.sin_port = htons(port);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(argv[1]);



    if(connect(sd,(struct sockaddr *)&server, sizeof(server)) == -1){
        perror("[client] connect");
        return -1;
    }

    printf("[client] M-am connectat la %s:%s\n", argv[1],argv[2]);

    while(1){

        char msg[512];
        printf("[client] Introduce-ti o comanda:\n");
        read(0,msg,sizeof(msg));

        printf("...\n");

        if(writen(sd,msg,strlen(msg)) == -1){
            perror("[client] write");
            return -1;
        }


        memset(msg,0,strlen(msg));

        unsigned int message_len_net = 0;
        if( readn(sd,&message_len_net, sizeof(message_len_net)) < 0 ){
            perror("[client] Read message len");
            return -1;
        }

        unsigned int message_len = ntohl(message_len_net);

        if(readn(sd,msg,message_len) < 0){
            perror("[client] Error read message");
            return -1;
        }

        msg[message_len] = '\0';

        printf("[client] Am primit reply: %s\n", msg);

        if(strcmp(msg, "Ok bye") == 0){
            break;
        }
    }




    return 0;
}