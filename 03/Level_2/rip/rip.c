/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 14:53:46 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/02/07 15:39:40 by Nikita_Kuyd      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rip.h"

int	ft_strlen(char	*str)
{
	int	i = 0;

	while (str[i])
		i++;
	return (i);
}

void    count_invalid_parenthesis(t_res *res, char *str)
{
	int    i = 0;
	
	while (str[i])
	{
		if (str[i] == '(')
			res->open++;
		else if (str[i] == ')')
		{
			if (res->open > 0)
				res->open--;
			else
				res->close++;
		}
		i++;
	}
}

void    backktrack(char *str, t_res	*s, int i, int balance, char *cur_res)
{
	if (i == ft_strlen(str))
	{
		if (balance == 0 && s->open == 0 && s->close == 0)
			puts(cur_res);
		return ;
	}
	if (str[i] == '(')
	{
		if (s->open > 0)
		{
			cur_res[i] = ' ';
			s->open--;
			backktrack(str, s, i + 1, balance, cur_res);
			s->open++;
		}
		cur_res[i] = '(';
		backktrack(str, s, i + 1, balance + 1, cur_res);
	}
	else if (str[i] == ')')
	{
		if (s->close > 0)
		{
			cur_res[i] = ' ';
			s->close--;
			backktrack(str, s, i + 1, balance, cur_res);
			s->close++;
		}
		if (balance > 0)
		{
			cur_res[i] = ')';
			backktrack(str, s, i + 1, balance - 1, cur_res);
		}
	}
}

int main(int argc, char **argv)
{
	t_res	*struc;
	char	*cur_res;

	(void)argc;
	struc = malloc(sizeof(t_res));
	if (!struc)
		return (0);
	struc->open = 0;
	struc->close = 0;
	cur_res = malloc(1 * (ft_strlen(argv[1]) + 1));
	if (!cur_res)
		return (0);
	cur_res[ft_strlen(argv[1])] = '\0';
	count_invalid_parenthesis(struc, argv[1]);
	backktrack(argv[1], struc, 0, 0, cur_res);
}
