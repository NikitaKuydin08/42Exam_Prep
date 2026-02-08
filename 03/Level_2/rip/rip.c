/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 16:06:00 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/02/07 16:31:06 by Nikita_Kuyd      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_res
{
    int open;
    int close;
}   t_res;

int ft_strlen(char *str)
{
    int i = 0;

    while (str[i])
        i++;
    return (i);
}

void    count_invalid_brackets(t_res *s, char *str)
{
    int i = 0;

    while (str[i])
    {
        if (str[i] == '(')
            s->open++;
        else if (str[i] == ')')
        {
            if (s->open > 0)
                s->open--;
            else
                s->close++;
        }
        i++;
    }
}

void    solve(char *str, t_res *s, int index, int balance, char *cur_result)
{
    if (index == ft_strlen(str)) // the first and only case to exit the recursion
    {
        if (balance == 0 && s->open == 0 && s->close == 0)
            puts(cur_result);
        return ;
    }
    if (str[index] == '(') // the first case, opening bracket
    {
        if (s->open > 0)
        {
            cur_result[index] = ' ';
            s->open--;
            solve(str, s, index + 1, balance, cur_result);
            s->open++;
        }
        cur_result[index] = '(';
        solve(str, s, index + 1, balance + 1, cur_result);
    }
    else if (str[index] == ')')
    {
        if (s->close > 0)
        {
            cur_result[index] = ' ';
            s->close--;
            solve(str, s, index + 1, balance, cur_result);
            s->close++;
        }
        if (balance > 0)
        {
            cur_result[index] = ')';
            solve(str, s, index + 1, balance - 1, cur_result);
        }
    }
}

int main(int argc, char **argv)
{
    char    *cur_result;
    t_res   *s;
    
    if (argc != 2)
        return (1);
    s = malloc(sizeof(t_res));
    if (!s)
        return (1);
    s->open = 0;
    s->close = 0;
    cur_result = malloc(sizeof(char) * (ft_strlen(argv[1]) + 1));
    if (!cur_result)
        return (1);
    cur_result[ft_strlen(argv[1])] = '\0';
    count_invalid_brackets(s, argv[1]);
    solve(argv[1], s, 0, 0, cur_result);
    free(s);
    free(cur_result);
    return (0);
}
