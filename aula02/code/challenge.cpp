#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "delays.h"
#include "process.h"

int main(void)
{
    printf("Before the fork: PID = %d, PPID = %d\n", getpid(), getppid());

    pid_t ret = pfork();
    if (ret == 0)
    {
        if(execl("./child_counter", "./child_counter" , NULL) == -1){
            printf("child_counter program does not exist!\n");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        pwait(NULL);
        printf("Child process finished!\n");
        printf("After the fork: PID = %d, PPID = %d\n", getpid(), getppid());
    }

    return EXIT_SUCCESS;
}
