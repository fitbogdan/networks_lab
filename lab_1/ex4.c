#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char* argv[]){

    for(int i = 0; i < strlen(argv[1]); i+=1){
        printf("%c", argv[1][i]);
    }

    struct stat f;
    int fd = open(argv[1][0], O_RDONLY);
    
    if(lstat(argv[1], &f)){
        perror("");
    }

    printf("\n%llu", f.st_mtim.tv_nsec);

    return 0;

}