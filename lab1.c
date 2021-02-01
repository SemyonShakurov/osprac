#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    printf("uid = %d, gid = %d\n", (int)getuid(), (int)getgid());
    return 0;
}
