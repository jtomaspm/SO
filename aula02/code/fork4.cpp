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
    if(execl("./child", "./child", NULL)==-1){
        printf("Error executing ./child");
        exit(EXIT_FAILURE);
    }
    printf("why doesn't this message show up?\n");
    return EXIT_FAILURE;
  }
  else
  {
    usleep(40000);
    printf("I'm the parent: PID = %d, PPID = %d\n", getpid(), getppid());
    pwait(NULL);
    printf("always after\n");
  }

  return EXIT_SUCCESS;
}
