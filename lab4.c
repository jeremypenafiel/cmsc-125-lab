#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

void* searchFileForWord(void *);
void* testFoo(void*);



int main(){

    pthread_t threads[3];
    char inp[] = "echo";
    char filename[] = "words1.txt";
    char* args[2] = {filename, inp};

    for(int i = 0; i < 3; i++){
        pthread_create(&threads[i], NULL, searchFileForWord, args);
    }

    // pthread_create(&threads[0], NULL, searchFileForWord, args);
    for(int i = 0; i < 3; i++){
        pthread_join(threads[i], NULL);
    }
    // pthread_join(threads[0], NULL);

    // printf("hello");
    // return 0;
}

void* searchFileForWord(void* args){
    char **arguments = (char**) args;
    char* fileName = arguments[0];
    char* wordToBeSearched = arguments[1];
    FILE *file = fopen(fileName, "r");
    char fileContents[2000];

    fread(fileContents, sizeof(fileContents), 1, file);

    // printf("%s", fileContents);
    char * pos = strstr(fileContents, wordToBeSearched);
    if(pos == NULL){
        printf("Word not found\n");     
    }else{
        printf("Word found\n");
        printf("%ld\n", pos-fileContents);
    }
    fclose(file);

    // printf("%s", &arguments[0] + 1);
    // printf("%s\n", arguments[0]);
    // printf("%s", arguments[1]);

}

void* testFoo(void* arg){
    char * arg1 =  arg;

    printf("%s", arg1);


}

