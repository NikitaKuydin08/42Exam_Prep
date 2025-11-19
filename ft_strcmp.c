/*
Assignment name  : ft_strcmp
Expected files   : ft_strcmp.c
Allowed functions:
--------------------------------------------------------------------------------

Reproduce the behavior of the function strcmp (man strcmp).

Your function must be declared as follows:

int    ft_strcmp(char *s1, char *s2);
*/

// i thought it would be just enough to loop through the strings while they are still equals to each other. But then there is a case when the strings are equals up to the null terminated, then we need to terminate from the loop by mentioning (s1[i] || s2[i]) explicitly.

#include <stdio.h>

int ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    while (s1[i] == s2[i] && (s1[i] || s2[i]))
        i++;
    return (s1[i] - s2[i]);
}

// int main(void)
// {
//     char    *s1;
//     char    *s2;

//     s1 = "Hello";
//     s2 = "Hell";
//     printf("%d", ft_strcmp(s1, s2));
// }
