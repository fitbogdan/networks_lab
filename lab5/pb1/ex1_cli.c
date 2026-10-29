#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>

#include "netio.h"


int main(int argc, char *argv[]){
    if(argc != 4){
        printf("[client] Folosire: %s <ip> <port> <numarul>\n", argv[0]);
    }

    int sd;			// descriptorul de socket
    struct sockaddr_in server;	// structura folosita pentru conectare 

    int port = atoi(argv[2]);
    

    if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("[client] Socket");
        return -1;
    }
      
    server.sin_family = AF_INET; //Type of socket (ipv4)
    server.sin_addr.s_addr = inet_addr(argv[1]); //IP of the server
    server.sin_port = htons(port); //Port of the server
    
    
    if( connect(sd, (struct sockaddr *)&server, sizeof( struct sockaddr)) == -1){
        perror("[client] Error la connect");
        close(sd);
        return -1;
    }
    
    int number = atoi(argv[3]);

    int net_send_num = htonl(number);

    if(writen(sd, &net_send_num, sizeof(net_send_num)) == -1){
        perror("[client] Error la write");
        close(sd);
        return -1;
    }

    int reply[2];

    if(readn(sd, reply, sizeof(reply)) != sizeof(reply)){
        perror("[client] Error la read");
        close(sd);
        return -1;
    }

    printf("[client] Result: id=%d, reply=%d\n", ntohl(reply[1]),ntohl(reply[0]));

    close(sd);
}