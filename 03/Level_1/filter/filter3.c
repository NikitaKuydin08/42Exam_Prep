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
    static char *stash;
    char        *buffer;
    char        *temp;
    char        *match;
    char        *pattern;
    int         stash_len = 0;
    int         bytes = 0;
    int         before_match = 0;
    int         pattern_len = 0;
    int         i = 0;
    int         j = 0;

    if (argc != 2 || argv[1][0] == '\0')
        return (1);
    buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buffer)
        return (error_mes());
    pattern = argv[1];
    pattern_len = strlen(pattern);
    stash = NULL;
    temp = NULL;
    while (1)
    {
        bytes = read(0, buffer, BUFFER_SIZE);
        if (bytes < 0)
            return (error_mes());
        if (bytes == 0)
            break ;
        // buffer[bytes] = '\0';
        temp = realloc(stash, stash_len + bytes);
        if (!temp)
            return (error_mes());
        stash = temp;
        memmove(stash + stash_len, buffer, bytes);
        stash_len += bytes;
        i = 0;
        while ((match = memmem(stash + i, stash_len - i, pattern, pattern_len)))
        {
            before_match = match - (stash + i);
            write(1, stash + i, before_match);
            j = 0;
            while (j < pattern_len)
            {
                write(1, "*", 1);
                j++;
            }
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
    free(stash);
    return (0);
}
