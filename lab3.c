#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int getInput();
int isPrime(int);

int main(){

    int userInput = getInput();

    //Created two pipes
    int parentPipe[2]; // parent uses this pipe to write on
    int childPipe[2];   // child uses this pipe to write on

    int isPrimeNumberParent;
    pid_t pid;

    printf("Parent writing to pipe...\n");

    pipe(parentPipe);
    pipe(childPipe);

    write(parentPipe[1], &userInput, sizeof(userInput));
    close(parentPipe[1]);

    pid = fork();

    if (!pid){  // if child process
        int number;
        int isPrimeNumberChild;

        // read from parentPipe
        printf("Child reading from pipe...\n");
        read(parentPipe[0], &number, sizeof(number));
        close(parentPipe[0]);


        //determine if prime
        printf("[Child] the number is: %d\n", number);
        isPrimeNumberChild = isPrime(number);


        // write to childPipe
        printf("Child writing to pipe...\n");
        write(childPipe[1], &isPrimeNumberChild, sizeof(isPrimeNumberChild));    
        close(childPipe[1]);
        exit(0);
    }

    // wait for process to finish
    wait(NULL);

    // read from childPipe
    printf("Parent reading from pipe...\n");
    read(childPipe[0], &isPrimeNumberParent, sizeof(isPrimeNumberParent));
    close(childPipe[0]);

    if(isPrimeNumberParent){
        printf("[Parent] %d is prime\n", userInput);
    } else {
        printf("[Parent] %d is not prime\n", userInput);

    }
    

    

    return 0;
}


int getInput(){
    int n, valid;

    printf("Enter a number: ");
    valid = scanf("%d", &n);

    return n;

}

int isPrime(int n){
    int i;
    for (i = 2; i <= n/2; i++){
        if (n % i == 0){
            return 0;
        }
    }
    return 1;
}


