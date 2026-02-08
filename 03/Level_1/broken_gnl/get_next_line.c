/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 16:45:25 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/02/06 20:15:36 by Nikita_Kuyd      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
    
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buffer)
        return (NULL);
    while (bytes > 0 && !ft_strchr(stash, '\n'))
    {
        bytes = read(fd, buffer, BUFFER_SIZE);
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