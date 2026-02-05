/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_prime_sum.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:06:46 by nkuydin           #+#    #+#             */
/*   Updated: 2025/11/07 15:42:25 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Assignment name  : add_prime_sum
Expected files   : add_prime_sum.c
Allowed functions: write, exit
--------------------------------------------------------------------------------

Write a program that takes a positive integer as argument and displays the sum
of all prime numbers inferior or equal to it followed by a newline.

If the number of arguments is not 1, or the argument is not a positive number,
just display 0 followed by a newline.

Yes, the examples are right.

Examples:

$>./add_prime_sum 5
10
$>./add_prime_sum 7 | cat -e
17$
$>./add_prime_sum | cat -e
0$
$>
*/

#include <unistd.h>

int	num_is_prime(int nb)
{
	int		check;

	check = 2;
	while (check <= nb / 2)
	{
		if (nb % check == 0)
			return (0);
		check++;
	}
	return (1);
}

void	ft_putnbr(int nb)
{
	char	num[10];
	int		i;

	i = 0;
	while (nb > 0)
	{
		num[i++] = nb % 10 + '0';
		nb = nb / 10;
	}
	while (i > 0)
		write(1, &num[--i], 1);
}

int	ft_atoi(char *str)
{
	int	i;
	int	result;
	int	sign;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i])
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	result = result * sign;
	return (result);
}

int	main(int argc, char **argv)
{
	int	num;
	int	sum;

	num = ft_atoi(argv[1]);
	sum = 0;
	if (argc == 2 && num > 0)
	{
		while (num > 1)
		{
			if (num_is_prime(num))
				sum += num;
			num--;
		}
		ft_putnbr(sum);
		write(1, "\n", 1);
	}
	else
		write(1, "0\n", 2);
}
