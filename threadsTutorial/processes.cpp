#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>


int main(int argc, char* argv[]){
    int x = 2;
    int pid = fork();
    if(pid == -1){
        return 1;
    }
    printf("Process id %d\n", getpid());

    //if we are on the child process
    if(pid == 0){
        x++;
    }

    sleep(2);
    printf("Value of x: %d\n", x);

    //wait for child process to finish
    if(pid != 0){
        wait(NULL);
    }
    return 0;
}
