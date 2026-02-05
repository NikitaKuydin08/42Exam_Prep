#include <unistd.h>

static void putword(char *str, int start, int end)
{
    while (start < end)
    {
        write(1, &str[start], 1);
        start++;
    }
}

void rostring(char *str)
{
    int i = 0;
    int start_first, end_first;
    int start, end;
    int printed = 0;

    // Skip leading spaces/tabs
    while (str[i] == ' ' || str[i] == '\t')
        i++;

    // Save first word
    start_first = i;
    while (str[i] && str[i] != ' ' && str[i] != '\t')
        i++;
    end_first = i;

    // Print OTHER words
    while (str[i])
    {
        // Skip spaces
        while (str[i] == ' ' || str[i] == '\t')
            i++;

        // Find next word
        start = i;
        while (str[i] && str[i] != ' ' && str[i] != '\t')
            i++;
        end = i;

        // Print this word if it exists
        if (end > start)
        {
            if (printed)
                write(1, " ", 1);
            putword(str, start, end);
            printed = 1;
        }
    }

    // Print FIRST WORD at the end
    if (end_first > start_first)
    {
        if (printed)
            write(1, " ", 1);
        putword(str, start_first, end_first);
    }
}

int main(int ac, char **av)
{
    if (ac > 1)
        rostring(av[1]);
    write(1, "\n", 1);
    return 0;
}
