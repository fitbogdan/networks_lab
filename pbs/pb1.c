#include <stdio.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char* argv[]){


    // ls -a -l
    //1: execl
    char* method = argv[1];


    int pid = fork();

    if(pid == -1){
        perror("fork error");
        return 1;
    }
    if(pid == 0){
        // Child work
        char* a[] = {"ls", "-l", "-a", NULL};
        if(strcmp(method, "execl") == 0){
            execl("/usr/bin/ls", "ls", "-l", "-a", NULL);
        }
        
        
        else if(strcmp(method, "execlp") == 0){
            execlp("/usr/bin/ls", "ls", "-l", "-a", NULL);
        }

        else if(strcmp(method, "execvp") == 0){
            execvp("/usr/bin/ls", a);
        }

        else if(strcmp(method, "execv") == 0){
            execv("/usr/bin/ls", a);
        }


        printf("something went wrong\n");
        printf("%s\n", method);
    }


    return 0;
}