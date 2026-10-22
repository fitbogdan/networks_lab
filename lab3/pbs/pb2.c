#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>


int main(int argc, char* argv[]){

    int sv[2];

    if(socketpair(AF_UNIX, SOCK_STREAM, 0, sv) == -1){
        perror("socket pair");
        return EXIT_FAILURE;
    }


    pid_t pid = fork();
    if(pid == -1){
        perror("Fork");
        return EXIT_FAILURE;
    }

    //child
    if(pid == 0){

        close(sv[0]);





    }

    close(sv[1]);


    if(write(sv[0], argv[1], strlen(argv[1])) == -1){
        perror("write la tata");
        return EXIT_FAILURE;
    }

    

    return 0;
}