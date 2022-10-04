#include <cstdint>
#include <cstdio>
#include <unistd.h>

int main(void){
    printf("I'm child process: PID = %d, PPID = %d\n", getpid(), getppid());
    for (uint32_t i = 1; i < 11; i++)
    { 
        printf ("\r%02u ", i);
        fflush (stdout);
        usleep(200000);
    }
    printf ("\n");
}
