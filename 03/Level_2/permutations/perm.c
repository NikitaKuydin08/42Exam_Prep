/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 12:35:51 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/02/02 19:56:00 by Nikita_Kuyd      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "perm.h"

int ft_strlen(char *str)
{
    int    i = 0;
    while (str[i])
        i++;
    return (i);
}

void    ft_swap(char*a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}

void    reverse(char *str, int left, int right)
{
    while (left < right)
    {
        ft_swap(&str[left], &str[right]);
        left++;
        right--;
    }
}

void    sort_str(char *str)
{
    int i = 0;
    int j = 0;

    while (i < ft_strlen(str) - 1)
    {
        j = i + 1;
        while (j < ft_strlen(str))
        {
            if (str[i] > str[j])
                ft_swap(&str[i], &str[j]);
            j++;
        }
        i++;
    }
}

int    next_permutation(char *str, int len)
{
    int i;
    int j;
    // acb
    i = len - 2; // i = 1 str[1] = c, c > b, i--, i = 0, str[0] = a, a < c
    while (i >= 0 && str[i] >= str[i + 1])
        i--;
    if (i < 0)
        return (0);
    j = len - 1; // j = 2
    while (str[i] >= str[j]) // str[0] = a, str[j] = b, a !> b, swap(a, b)
        j--;
    ft_swap(&str[i], &str[j]); // acb -> bca
    reverse(str, i + 1, len - 1); // take c, swap it with a. 
    return (1);
}

int main(int argc, char **argv)
{
    char    *str;
    int     i;

    (void)argc;
    str = malloc(sizeof(char) * (ft_strlen(argv[1])));
    if (!str)
        return (0);
    for (i = 0; i < ft_strlen(argv[1]); i++)
        str[i] = argv[1][i];
    str[i] = '\0';
    sort_str(str);
    puts(str);
    while (next_permutation(str, ft_strlen(argv[1])))
        puts(str);
}
