#include "shell.h"

int main()
{
    pid_t parent_pid;
    /*getppid function not working on windows*/
    parent_pid = getppid();
    printf("%u\n", parent_pid);
    return (0);
}