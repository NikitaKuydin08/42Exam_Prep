/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picoshell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-03-26 02:27:47 by Nikita_Kuydin     #+#    #+#             */
/*   Updated: 2026-03-26 02:27:47 by Nikita_Kuydin    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Allowed functions:	close, fork, wait, exit, execvp, dup2, pipe

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// void    create_pipes(int (*pipefd)[2], int n)
// {
//     int i;

//     i = 0;
//     if (pipefd == -1)
//         return (1);
//     while (i < n - 1)
//     {
//         pipe(pipefd[i]);
//         i++;
//     }
// }

// void    close_pipes(int (*pipefd)[2], int n)
// {
//     int i;

//     i = 0;
//     while (i < n - 1)
//     {
//         if (pipefd[i][0] >= 0)
//             close(pipefd[i][0]);
//         if (pipefd[i][1] >= 0)
//             close(pipefd[i][1]);
//         i++;
//     }
// }

// void    duplicate_fds(int num_cmd, int (*pipefd)[2], int n)
// {
//     if (num_cmd != 0)
//     {
//         if (dup2(pipefd[num_cmd - 1][0], STDIN_FILENO) == -1)
//             exit(1);
//         close(pipefd[num_cmd - 1][0]);
//     }
//     if (num_cmd != n - 1)
//     {
//         close(pipefd[num_cmd][0]);
//         if (dup2(pipefd[num_cmd][1], STDOUT_FILENO) == -1)
//             exit(1);
//         close(pipefd[num_cmd][1]);
//     }
// }

int wait_for_all()
{
    int status;
    int exit_status;

    exit_status = 0;
    while (wait(&status) != -1)
    {
        if (WIFEXITED(status))
            exit_status = WEXITSTATUS(status);
    }
    return (exit_status);
}

int    picoshell(char **cmds[])
{
    size_t  i;
    int     prev_read_fd;
    int     pipefd[2];
    pid_t   pid;

    i = 0;
    if (!cmds || !cmds[0])
        return (0);
    prev_read_fd = -1;
    while (cmds[i])
    {
        if (cmds[i + 1])
        {
            if (pipe(pipefd) == -1)
                return (1);
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
                return (1);
            }
        }
        if (pid == 0)
        {
            if (prev_read_fd != -1)
            {
                if (dup2(prev_read_fd, STDIN_FILENO) == -1)
                    exit(1);
                close(prev_read_fd);
            }
            if (cmds[i + 1])
            {
                close(pipefd[0]);
                if (dup2(pipefd[1], STDOUT_FILENO) == -1)
                    exit(1);
                close(pipefd[1]);
            }
            execvp(cmds[i][0], cmds[i]);
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
    return (wait_for_all());
}

//  static int count_cmds(int argc, char **argv)
//  {
//      int count = 1;
//      for (int i = 1; i < argc; i++)
//      {
//          if (strcmp(argv[i], "|") == 0)
//              count++;
//      }
//      return count;
//  }

//  int main(int argc, char **argv)
//  {
//      if (argc < 2)
//          return (fprintf(stderr, "Usage: %s cmd1 [args] | cmd2 [args] ...\n", argv[0]), 1);

//      int cmd_count = count_cmds(argc, argv);
//      char ***cmds = calloc(cmd_count + 1, sizeof(char **));
//      if (!cmds)
//          return (perror("calloc"), 1);

//      // Parse arguments and build command array
//      int i = 1, j = 0;
//      while (i < argc)
//      {
//          int len = 0;
//          while (i + len < argc && strcmp(argv[i + len], "|") != 0)
//              len++;

//          cmds[j] = calloc(len + 1, sizeof(char *));
//         if (!cmds[j])
//             return (perror("calloc"), 1);

//         for (int k = 0; k < len; k++)
//             cmds[j][k] = argv[i + k];
//         cmds[j][len] = NULL;

//          i += len + 1;  // Skip the "|"
//         j++;
//     }
//     cmds[cmd_count] = NULL;

//     int ret = picoshell(cmds);

//      // Free memory
//     for (int i = 0; cmds[i]; i++)
//         free(cmds[i]);
//     free(cmds);

//     return ret;
// }
