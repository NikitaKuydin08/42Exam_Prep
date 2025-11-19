/*
Assignment name	: ft_strcspn
Expected files	: ft_strcspn.c
Allowed functions: None
---------------------------------------------------------------

Reproduce exactly the behavior of the function strcspn
(man strcspn).

The function should be prototyped as follows:

size_t	ft_strcspn(const char *s, const char *reject);
*/

// pretty straightforward loop trough both of strings if we find that the character equals in both strings, we return i, it means that that the i now the number of characters before finding the same character

#include <stdio.h>

size_t  ft_strcspn(const char *s, const char *reject)
{
    size_t i;
    size_t j;

    i = 0;
    while (s[i])
    {
        j = 0;
        while (reject[j])
        {
            if (s[i] == reject[j])
                return (i);
            j++;
        }
        i++;
    }
    return (i);
}

// int main(void)
// {
//     printf("%d", ft_strcspn("ffffff", "f"));
// }
