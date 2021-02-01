#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    printf("my pid = %d,my ppid = %d", (int)getpid(), (int) getppid());
    return 0;
}
