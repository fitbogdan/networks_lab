#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

//S1:

/*
int main(int argc, char* argv[]){

    int pid = fork();

    if(pid == -1){
        perror("fork error");
        return 1;
    }
    if(pid == 0){
        // Child work
        int fd;
        while((fd = open("mesaj.txt", O_RDONLY)) == -1){
            usleep(100*100);
        }
        char msg[32];
        ssize_t n = read(fd, msg, sizeof(msg)-1);
        close(fd);

        if(n < 0){
            perror("read");
            return EXIT_FAILURE;
        }

        usleep(1000*300);

        printf("[fiul] Msj: %s\n", msg);

        return EXIT_SUCCESS;

    }
    //PARENT()
    const char* msg = (pid%2 == 0) ? "fortune" : "lost";

    //Write in mesaj.text


    int fd = open("msj_tmp.txt", O_RDWR | O_CREAT, 0644);
    if(fd == -1 || write(fd, msg, strlen(msg)) == -1){
        perror("Eroare la open");
        return EXIT_FAILURE;
    }
    close(fd);
    rename("msj_tmp.txt", "mesaj.txt");




    if(pid%2 != 0){
        // Tatal trebuie sa termine primul
        printf("[tata] %d impar, exit\n", pid);
        return EXIT_SUCCESS;
    }


    printf("[tata] Parinte: astept fiul: %d\n", pid);

    wait(NULL);


    return EXIT_SUCCESS;
}


*/



int main(int argc, char* argv[]){



    int pid = fork();

    if(pid == -1){
        perror("fork error");
        return 1;
    }
    if(pid == 0){


    }


    return 0;
}