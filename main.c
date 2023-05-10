#include "shell.h"

int main()
{
    pid_t parent_pid;
    parent_pid = getppid();
    printf("%u\n", parent_pid);
    return (0);
}