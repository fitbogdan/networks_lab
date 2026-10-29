#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "netio.h"

void extract_command(FILE* fp, int chosen_number, char* command){
    rewind(fp);
    ssize_t read = 0;
    char* line = NULL;
    ssize_t len = 0;

    while((read = getline(&line, &len, fp)) != -1){
        // printf("Read line: %s", line);

        // printf("The ln: %ld\n", read);

        int separator = 0;

        for(int i = 0; i < read; i++){
            if(line[i] == ':'){
                separator = i;
                break;
            }
        }

        if(separator == 0){
            fprintf(stderr, "Wrong file format in fisier.txt: %s\n",line);
            continue;
        }
        
        //Extrag nr
        char nr[128];
        size_t n = separator;
        // memcpy(nr,line,n);
        nr[n] = '\0';
        strncpy(nr, line, n);
        if(atoi(nr) != chosen_number){
            continue;
        }


        //Extrag comanda
        memset(command, 0, sizeof(command));


        strcpy(command,line+n+1);


        command[strcspn(command, "\n")-1] = '\0';

        free(line);
        break;
    }   

    // strcpy(out,command);
}

void run_command(char* command, int client){
    pid_t pid = fork();

    printf("%s\n",command);
    if(pid == 0){
        dup2(client, STDOUT_FILENO);
        execl(command,command,NULL);
        perror("[server - child] Execl");
        _exit(1);
    }
}
int main(){


    FILE* fp = fopen("fisier.txt", "r");
    if(fp == NULL){
        return -1;
    }

    char command[128];

    //tcp_listen:

    struct sockaddr_in server;
    struct sockaddr_in from;

    int sd;

    if((sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1){
        perror("[server]socket");
        return -1;
    }

    server.sin_family = AF_INET; server.sin_port = htons(2024);
    server.sin_addr.s_addr = htonl(INADDR_ANY);


    if (bind (sd, (struct sockaddr *) &server, sizeof (struct sockaddr)) == -1){
        perror("[server] eroare la bind");
        return -1;
    }


    if(listen(sd,5) == -1){
        perror("[server] listen");
        return -1;
    }
    while(1){
        printf("[server] Ascult pe portul 2024\n");


        int length = sizeof(from);


        int client = accept(sd, (struct sockaddr *)&from, &length);


        if(client == -1){
            perror("[server] Eroare la accept");

            continue;
        }

        int key_net = 0;
        if(readn(client, &key_net, sizeof(key_net)) != sizeof(key_net)){
            perror("[server] Eroare la read");
            close(client);
            continue;
        }

        int key = ntohl(key_net);
        memset(command, 0, sizeof(command));


        extract_command(fp,key,command);

        run_command(command,client);

        close(client);


    }

    close(sd);

    // pid_t pid = fork();
    // if(pid == 0){ // Child
    //     execl(command,command,NULL);
    //     perror("execl");
    //     _exit(1);
    // }



    return 0;
}
