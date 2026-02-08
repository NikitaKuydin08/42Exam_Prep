/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_perm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 16:02:27 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/02/08 16:36:35 by Nikita_Kuyd      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int ft_strlen(char *str)
{
    int i = 0;

    while (str[i])
        i++;
    return (i);
}

void    ft_swap(char *a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}

void    ft_reverse(char *str, int left, int right)
{
    while (left < right)
    {
        ft_swap(&str[left], &str[right]);
        left++;
        right--;
    }
}

void    sort_str(char *str, int len)
{
    int i = 0;
    int j = 0;

    while (i < len)
    {
        j = i + 1;
        while (j < len)
        {
            if (str[i] > str[j])
                ft_swap(&str[i], &str[j]);
            j++;
        }
        i++;
    }
}

int next_permutation(char *str, int len)
{
    int i = len - 2;
    int j = len - 1; 

    while (i >= 0 && str[i] >= str[i + 1])
        i--;
    if (i < 0)
        return (-1);
    while (str[i] >= str[j])
        j--;
    ft_swap(&str[i], &str[j]);
    ft_reverse(str, i + 1, len - 1);
    return (0);
}

int main(int argc, char **argv)
{
    char *str;
    int i = 0;
    int len = 0;

    if (argc != 2 || argv[1][0] == '\0')
        return (1);
    len = ft_strlen(argv[1]);
    str = malloc(sizeof(char) * (len + 1));
    if (!str)
        return (1);
    while (i < len)
    {
        str[i] = argv[1][i];
        i++;
    }
    str[i] = '\0';
    sort_str(str, len);
    puts(str);
    while (next_permutation(str, len) == 0)
        puts(str);
    free(str);
    return (0);
}
