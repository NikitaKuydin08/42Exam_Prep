/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_mult.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 16:55:54 by nkuydin           #+#    #+#             */
/*   Updated: 2025/11/21 19:03:49 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Assignment name  : tab_mult
Expected files   : tab_mult.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that displays a number's multiplication table.

The parameter will always be a strictly positive number that fits in an int,
and said number times 9 will also fit in an int.

If there are no parameters, the program displays \n.

Examples:

$>./tab_mult 9
1 x 9 = 9
2 x 9 = 18
3 x 9 = 27
4 x 9 = 36
5 x 9 = 45
6 x 9 = 54
7 x 9 = 63
8 x 9 = 72
9 x 9 = 81
$>./tab_mult 19
1 x 19 = 19
2 x 19 = 38
3 x 19 = 57
4 x 19 = 76
5 x 19 = 95
6 x 19 = 114
7 x 19 = 133
8 x 19 = 152
9 x 19 = 171
$>
$>./tab_mult | cat -e
$
$>
*/

#include <unistd.h>

void	ft_putnbr(int nbr)
{
	char	num[10];
	int		i;

	i = 0;
	while (nbr != 0)
	{
		num[i] = nbr % 10 + '0';
		nbr /= 10;
		i++;
	}
	while (i > 0)
		write(1, &num[--i], 1);
}

int	ft_atoi(char *str)
{
	int	result;
	int	i;

	i = 0;
	result = 0;
	while (str[i])
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

int	main(int argc, char **argv)
{
	int	i;
	int	input;
	int	res;

	input = 0;
	i = 1;
	if (argc > 1)
	{
		input = ft_atoi(argv[1]);
		while (i <= 9)
		{
			res = 0;
			ft_putnbr(i);
			write(1, " x ", 3);
			ft_putnbr(input);
			write(1, " = ", 3);
			res = i * input;
			ft_putnbr(res);
			write(1, "\n", 1);
			i++;
		}
	}
	if (argc == 1)
		write(1, "\n", 1);
	return (0);
}
