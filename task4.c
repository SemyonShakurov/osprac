#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[], char* envp[])
{
  pid_t pid, ppid;
  pid = getpid();
  ppid = getppid();

  fork();

  if(getppid() == pid){
    (void)execle("/bin/cat", "/bin/cat", "task3.c", 0, envp);
    printf("Error on program start\n");
    exit(-1);
  }
  else{
    
  }
 
  return 0;
}
