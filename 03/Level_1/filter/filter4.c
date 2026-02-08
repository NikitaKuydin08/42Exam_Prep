/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 15:46:48 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/02/08 01:04:06 by Nikita_Kuyd      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef BUFFER_SIZE 
# define BUFFER_SIZE 42
#endif

int error_mes(void)
{
    perror("Error: ");
    return (1);
}

int main(int argc, char **argv)
{
    char    *buffer;
    int     bytes = 0;
    static char *stash;
    int         stash_len = 0;
    char        *temp;
    char        *pattern;
    int         pattern_len = 0;
    char        *match;
    int         before_match = 0;
    int         i = 0;
    int         j = 0;

    if (argc != 2 || argv[1][0] == '\0')
        return (error_mes());
    buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
    if (!buffer)
        return (error_mes());
    pattern = argv[1];
    pattern_len = strlen(pattern);
    temp = NULL;
    stash = NULL;
    while (1)
    {
        bytes = read(0, buffer, BUFFER_SIZE);
        if (bytes < 0)
            return (error_mes());
        if (bytes == 0)
            break ;
        buffer[bytes] = '\0';
        temp = realloc(stash, stash_len + bytes);
        if (!temp)
            return (error_mes());
        stash = temp;
        memmove(stash + stash_len, buffer, bytes);
        stash_len += bytes;
        free(buffer);
        i = 0;
        while ((match = memmem(stash + i, stash_len - i, pattern, pattern_len)))
        {
            before_match = match - (stash + i);
            write(1, stash + i, before_match);
            for(j = 0; j < pattern_len; j++)
                write(1, "*", 1);
            i += before_match + pattern_len;
        }
        if (i > 0)
        {
            memmove(stash, stash + i, stash_len - i);
            stash_len -= i;
            temp = realloc(stash, stash_len);
            if (!temp && stash_len > 0)
                return (error_mes());
            stash = temp;
        }
    }
    if (stash_len > 0)
        write(1, stash, stash_len);
    free(buffer);
    free(stash);
    return (0);
}
