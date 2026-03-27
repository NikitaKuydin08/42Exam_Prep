#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int    picoshell(char **cmds[])
{
    int pipefd[2];
    pid_t   pid;
    int     i;
    int     prev_read_fd;

    i = 0;
    prev_read_fd = -1;
    while (cmds[i])
    {
        if (cmds[i + 1])
        {
            if (pipe(pipefd) == -1)
            {
                if (prev_read_fd != -1)
                    close(prev_read_fd);
                return (1);
            }
        }
        pid = fork();
        if (pid == -1)
        {
            if (prev_read_fd != -1)
                close(prev_read_fd);
            if (cmds[i + 1])
            {
                close(pipefd[0]);
                close(pipefd[1]);
            }
            return (1);
        }
        if (pid == 0)
        {
            if (prev_read_fd != -1)
            {
                dup2(prev_read_fd, 0);
                close(prev_read_fd);
            }
            if (cmds[i + 1])
            {
                close(pipefd[0]);
                dup2(pipefd[1], 1);
                close(pipefd[1]);
            }
            execvp(cmds[i][0], cmds);
            exit(1);
        }
        if (prev_read_fd != -1)
            close(prev_read_fd);
        if (cmds[i + 1])
        {
            close(pipefd[1]);
            prev_read_fd = pipefd[0];
        }
        i++;
    }
    while (wait(NULL) > 0)
        ;
    return (0);
}