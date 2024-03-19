#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void nestedfork();



int main() {
    nestedfork();
    return 0;
}

void nestedfork(){
    printf("L0\n");
    

    if (fork() && fork())
    {
        printf("L1\n");
        fork();
    }
    
    printf("BYE\n");
} 
