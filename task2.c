#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
  pid_t pid, ppid;
  int a = 0;

  pid = getpid();
  ppid = getppid();

  fork();
  a = a+1;

  if(getppid() == pid)
  {
    printf("Second proccess: My pid = %d, my ppid = %d, result = %d\n", (int)getpid(), (int)getppid(), ++a);
  }
  else
  {
    printf("First proccess: My pid = %d, my ppid = %d, result = %d\n", (int)pid, (int)ppid, a);
  }
 
  return 0;
}
