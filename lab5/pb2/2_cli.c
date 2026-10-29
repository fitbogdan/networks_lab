#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

// Run with ./nume <ip> <port> <key>
int main(int argc, char* argv[]){

    if(argc < 4){
        fprintf(stderr, "run with: ./nume <ip> <port> <key>\n");
        return -1;
    }

    struct sockaddr_in server;
    int port = atoi(argv[2]);
    server.sin_family = AF_INET; //ipv4
    server.sin_addr.s_addr = inet_addr(ntohl(argv[1]));

    server.sin_port = htons(port); //Pentru ca e pe 16 biti, iar in memorie e in little endian
                                   //sin_port e 16 biti. htonl pe port are da primii biti (cei care ii ia sin_port)
                                   //0, pentru ca da flip la tot numarul
    int sd = 0; 

    if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("[client] socket");
        return -1;
    }

    if( connect(sd, (struct sockaddr *)&server, sizeof(struct sockaddr)) ==-1 ){
        perror("[client] eroare la connect");
        return -1;
    }

    

    




    return 0;
}