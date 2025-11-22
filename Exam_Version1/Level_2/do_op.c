/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 11:44:02 by nkuydin           #+#    #+#             */
/*   Updated: 2025/11/04 10:42:30 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/*
Assignment name  : do_op
Expected files   : *.c, *.h
Allowed functions: atoi, printf, write
--------------------------------------------------------------------------------

Write a program that takes three strings:
- The first and the third one are representations of base-10 signed integers
	that fit in an int.
- The second one is an arithmetic operator chosen from: + - * / %

The program must display the result of the requested arithmetic operation,
followed by a newline. If the number of parameters is not 3, the program
just displays a newline.

You can assume the string have no mistakes or extraneous characters. Negative
numbers, in input or output, will have one and only one leading '-'. The
result of the operation fits in an int.

Examples:

$> ./do_op "123" "*" 456 | cat -e
56088$
$> ./do_op "9828" "/" 234 | cat -e
42$
$> ./do_op "1" "+" "-43" | cat -e
-42$
$> ./do_op | cat -e
$
*/

int		ft_atoi(char *str);
void	ft_putnbr(int i);

int	main(int argc, char **argv)
{
	int		i;
	int		num1;
	int		num2;
	int		result;
	char	num[10];

	i = 0;
	num1 = 0;
	num2 = 0;
	result = 0;
	if (argc == 4)
	{
		num1 = ft_atoi(argv[1]);
		num2 = ft_atoi(argv[3]);
		if (argv[2][0] == '+')
			result = num1 + num2;
		else if (argv[2][0] == '-')
			result = num1 - num2;
		else if (argv[2][0] == '*')
			result = num1 * num2;
		else if (argv[2][0] == '/')
			result = num1 / num2;
		else if (argv[2][0] == '%')
			result = num1 % num2;
		ft_putnbr(result);
	}
	write(1, "\n", 1);
	return (0);
}

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	if (str[0] == '-')
	{
		sign *= -1;
		i++;
	}
	while (str[i])
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	result *= sign;
	return (result);
}

void	ft_putnbr(int i)
{
	char	num[10];
	int		c;

	c = 0;
	if (i == 0)
	{
		write(1, "0", 1);
		return ;
	}
	if (i == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (i < 0)
	{
		write(1, "-", 1);
		i *= -1;
	}
	while (i > 0)
	{
		num[c++] = i % 10 + '0';
		i = i / 10;
	}
	while (c > 0)
		write(1, &num[--c], 1);
}
