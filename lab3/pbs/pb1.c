#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int is_prime(long n){
    if(n < 2)
        return 0;
    if(n != 2 && n%2 == 0)
        return 0;
    
    for(long i = 3; i*i <= n; i+=2){
        if(n%i == 0) return 0;
    }

    return 1;
}

int main(int argc, char* argv[]){
    int fd[2];
    int fd2[2];
    if(pipe(fd) == -1){
        perror("Pipe");
        return EXIT_FAILURE;
    }

    if(pipe(fd2) == -1){
        perror("Pipe2");
        return EXIT_FAILURE;
    }

    int pid = fork();

    if(pid == -1){
        perror("Fork");
        return EXIT_FAILURE;
    }


    //Child
    if(pid == 0){

        close(fd[1]);
        close(fd2[0]);


        long value;
        ssize_t n;
        /* 0 = toți scriitorii au închis */
        if (read(fd[0], &value, sizeof value) != sizeof value)  {
            exit(EXIT_FAILURE);
        }
        
        printf("[fiul] Am primit msj\n");
        const char* msg = is_prime(value) ? "Yes" : "No";



        if (write(fd2[1], msg, strlen(msg)) == -1){
            perror("write");
            exit(EXIT_FAILURE);
        }

            
        printf("[fiul] Am trimis msj\n");

        exit(EXIT_SUCCESS);
    }
    // 0 = read end, 1 = write end
    close(fd[0]);
    close(fd2[1]);

    long n = atoi(argv[1]);

    if(write(fd[1], &n, sizeof n) == -1){
        perror("Write la tata");
        return EXIT_FAILURE;
    }


    printf("[tata] Am trimis msj\n");

    char answer[8];
    memset(answer, 0, 8);
    if(read(fd2[0], answer, sizeof answer -1) == -1){
        perror("Read tata");
        return EXIT_FAILURE;
    }

    printf("[tata] Am primit msj\n");


    printf("%s", answer);

    return 0;
}