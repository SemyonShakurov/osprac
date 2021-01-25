#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    printf("Your pid = %d, your ppid = %d\n", (int)getpid(), (int)getppid());
    return 0;
}
