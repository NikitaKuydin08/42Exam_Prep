/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_rip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 18:09:51 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/02/08 18:44:48 by Nikita_Kuyd      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

typedef struct s_set
{
    int close;
    int open;
}   t_set;

int ft_strlen(char *str)
{
    int i = 0;

    while (str[i])
        i++;
    return (i);
}

void    count_invalid_brackets(t_set *s, char *str)
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

void    solve(char *str, t_set *s, int i, int balance, char *cur_res)
{
    if (i == ft_strlen(str))
    {
        if (balance == 0 && s->close == 0 && s->open == 0)
            puts(cur_res);
        return ;
    }
    if (str[i] == '(')
    {
        if (s->open > 0)
        {
            cur_res[i] = ' ';
            s->open--;
            solve(str, s, i + 1, balance, cur_res);
            s->open++;
        }
        cur_res[i] = '(';
        solve(str, s, i + 1, balance + 1, cur_res);
    }
    else if (str[i] == ')')
    {
        if (s->close > 0)
        {
            cur_res[i] = ' ';
            s->close--;
            solve(str, s, i + 1, balance, cur_res);
            s->close++;
        }
        if (balance > 0)
        {
            cur_res[i] = ')';
            solve(str, s , i + 1, balance - 1, cur_res);
        }
    }
}

int main(int argc, char **argv)
{
    t_set s;

    if (argc != 2 || argv[1][0] == '\0')
        return (1);
    int len = ft_strlen(argv[1]);
    char    cur_res[len + 1];
    s.open = 0;
    s.close = 0;
    cur_res[len] = '\0';
    count_invalid_brackets(&s, argv[1]);
    solve(argv[1], &s, 0, 0, cur_res);
    return (0);
}
