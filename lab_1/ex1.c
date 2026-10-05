#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char* argv[]){
    
    if(argc >=2){
        char* filename = argv[1];

        if(filename == NULL){
            perror("No filename entered");
            return 1;
        }



        FILE* fp = fopen(argv[1], "r");

        char ** lines = NULL;
        size_t count = 0, cap = 0;
        char* line = NULL;

        size_t len = 0;

        while(getline(&line, &len, fp) != -1){
            //increase size:
            if(count == cap){
                cap = cap ? 2 * cap : 64;
                char ** tmp = realloc(lines, cap*sizeof(char*));

                if(tmp == NULL){
                    perror("realloc");
                    return 1;
                }

                lines = tmp;
            }


            if((lines[count++] = strdup(line)) == NULL){
                perror("stdup not working");
                return 1;
            }
        }

        for (int i = count-1; i >= 0; i--){
            printf("%s\n" , lines[i]);
        }
    }


    

    return 0;
}