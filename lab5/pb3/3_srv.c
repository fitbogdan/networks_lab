#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include<sys/socket.h>
#include "netio.h"
#include <string.h>
#include <pwd.h>


#define PORT 2024

int send_message(int fd, void* data, unsigned int len){
    unsigned int ln = htonl(len);
    if(writen(fd,&ln,sizeof(ln)) == -1){
        perror("[server] Eroare la write");
        return -1;
    }

    return writen(fd,data,len);
}

int main(){

    struct sockaddr_in server;
    struct sockaddr_in from;
    
    // Set up socket for communicating with client
    
    int sd;
    if( (sd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){
        perror("[server] Socket");
        return -1;
    }

    int on = 1;
    setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof on);
    
    //Configure server:

    memset(&server, 0, sizeof(server));
    memset(&from, 0, sizeof(from));


    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = htonl(INADDR_ANY);


    //Bind socket to server. (Tell the kernel that this socket is used for this server adress)

    if( bind(sd, (struct sockaddr *)&server, sizeof(server)) == -1 ){
        perror("[server] Eroare la bind");
        return -1;
    }


    //Start listening on INADDR_ANY with port PORT (2024)

    if( listen(sd, 5) == -1 ){
        perror("[server] Eroare la listen");
        return -1;
    }
    printf("[server] Listening on port 2024\n");
    

    while(1){
        int len = sizeof(from);
        int client = accept(sd, (struct sockaddr *)&from, &len);
        int logged = 0;

        if(client == -1){
            perror("[server] Bad connection");
            return -1;
        }

        printf("[server] Accepted client\n");

        char line[512];
        memset(line,0,sizeof(line));
        if(read_line(client,line,sizeof(line)) < 0){
            break;
        }

        char* cmd = strtok(line, " \t");
        char* arg = strtok(NULL, " \t");

        if(cmd == NULL){
            char* msg = "Your command was not recieved, its null";
            unsigned int len = strlen(msg);
            send_message(client,msg,len);
            close(client);
            continue;
        }
        else if(strcmp(cmd, "quit") == 0){
            char* msg = "Ok bye";
            send_message(client,msg,strlen(msg));
            close(client);
            continue;
        }
        else if(strcmp(cmd, "login") == 0){
            if(arg != NULL && getpwnam(arg) != NULL){
                logged = 1;
                char* msg = "Welcome! You are logged in.";
                send_message(client,msg,strlen(msg));
            }
            else if(arg == NULL){
                char* msg = "Error, provide a username";
                send_message(client,msg,strlen(msg));
            }
            else if(getpwnam(arg) == NULL){
                char* msg = "Error, invalid username";
                send_message(client,msg,strlen(msg));
            }
        }
    }


    return 0;

}