#include <stdio.h>
#include <unistd.h>

int main(void)
{
    pid_t child_pid;

    child_pid = fork();
    if (child_pid == -1)
    {
        perror("fork");
        return (1);
    }
    if (child_pid == 0)
        printf("Child Process. PID: %d\n", getpid());
    else
        printf("Parent Process. PID: %d\n", child_pid);
    return (0);
}
