/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_popen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-03-25 04:32:29 by Nikita_Kuydin     #+#    #+#             */
/*   Updated: 2026-03-25 04:32:29 by Nikita_Kuydin    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int ft_strlen(char *str)
{
    int i = 0;

    if (!str)
        return (0);
    while (str[i])
        i++;
    return (i);
}

char    *ft_strjoin(char *s1, char *s2)
{
    int i = 0;
    int j = 0;
    int s1_len = ft_strlen(s1);
    int s2_len = ft_strlen(s2);
    char    *dest;
    
    dest = malloc(sizeof(char) * (s1_len + s2_len + 1));
    if (!dest)
        return (NULL);
    while (i < s1_len)
    {
        dest[i] = s1[i];
        i++;
    }
    while (j < s2_len)
    {
        dest[i + j] = s2[j];
        j++;
    }
    dest[i + j] = '\0';
    free(s1);
    return (dest);
}

char    *ft_strchr(char *str, char c)
{
    int i = 0;

    if (!str)
        return (NULL);
    while(str[i])
    {
        if (str[i] == c)
            return (str + i);
        i++;
    }
    return (NULL); 
}

char *get_next_line(int fd)
{
    static char *stash;
    int         stash_len = 0;
    char        *buffer;
    int         bytes = 1;
    char        *line;
    int         line_len = 0;
    int         i = 0;
    int         j = 0;
    char        *new_stash;
    
    if (fd < 0 || 1 <= 0)
        return (NULL);
    buffer = malloc(sizeof(char) * (1 + 1));
    if (!buffer)
        return (NULL);
    while (bytes > 0 && !ft_strchr(stash, '\n'))
    {
        bytes = read(fd, buffer, 1);
        if (bytes < 0)
        {
            free(buffer);
            return (NULL);
        }
        if (bytes == 0)
            break ;
        buffer[bytes] = '\0';
        stash = ft_strjoin(stash, buffer);
    }
    free(buffer);
    if (!stash || stash[0] == '\0')
    {
        free(stash);
        stash = NULL;
        return (NULL);
    }
    while (stash[i] && stash[i] != '\n')
        i++;
    if (stash[i] == '\n')
        i++;
    line_len = i;
    line = malloc(sizeof(char) * (line_len + 1));
    if (!line)
    {
        free(stash);
        stash = NULL;
        return (NULL);
    }
    while (j < line_len)
    {
        line[j] = stash[j];
        j++;
    }
    line[j] = '\0';
    if (stash[i] != '\0')
    {
        while (stash[i + stash_len])
            stash_len++;
        new_stash = malloc(sizeof(char) * (stash_len + 1));
        if (!new_stash)
        {
            free(stash);
            stash = NULL;
            return (NULL);
        }
        j = 0;
        while (j < stash_len)
        {
            new_stash[j] = stash[j + i];
            j++;
        }
        new_stash[j] = '\0';
        free(stash);
        stash = new_stash;
    }
    else
    {
        free(stash);
        stash = NULL;
    }
    return (line);
}

// int main(void)
// {
//     int fd;
//     char    *line;

//     fd = open("file.txt", O_RDONLY);
//     line = get_next_line(fd);
//     while (line != NULL)
//     {
//         printf("%s", line);
//         free(line);
//         line = get_next_line(fd);
//     }
//     return (0);
// }

int ft_popen(const char *file, char *const argv[], char type)
{
    int     pipefd[2];
    pid_t   pid;

    if (!file || !argv || (type != 'r' && type != 'w'))
        return (-1);
    if (pipe(pipefd) == -1)
        return (-1);
    pid = fork();
    if (pid == -1)
    {
        close(pipefd[0]);
        close(pipefd[1]);
        return (-1);
    }
    if (pid == 0)
    {
        if (type == 'r')
        {
            close(pipefd[0]);
            dup2(pipefd[1], STDOUT_FILENO);
            close(pipefd[1]);
        }
        else
        {
            close(pipefd[1]);
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[0]);
        }
        execvp(file, argv);
        exit(1);
    }
    if (type == 'r')
    {
        close(pipefd[1]);
        return (pipefd[0]);
    }
    else
    {
        close(pipefd[0]);
        return (pipefd[1]);
    }
}

// int main()
// {
// 	int  fd;
// 	char *line;

// 	fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
// 	while ((line = get_next_line(fd)))
// 		printf("%s", line);
// 	return (0);
// }

// int	main() {
// 	int	fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
// 	dup2(fd, 0);
// 	fd = ft_popen("grep", (char *const []){"grep", "c", NULL}, 'r');
// 	char	*line;
// 	while ((line = get_next_line(fd)))
// 		printf("%s", line);
// }

int main()
{
    int fd = ft_popen("grep", (char *const []){"grep", "hello", NULL}, 'w');
    write(fd, "hello world\n", 12);
    write(fd, "bye world\n", 10);
    close(fd);
}
