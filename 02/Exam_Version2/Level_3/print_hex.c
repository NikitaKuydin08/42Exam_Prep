/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 20:47:35 by nkuydin           #+#    #+#             */
/*   Updated: 2025/11/21 21:07:08 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Assignment name  : print_hex
Expected files   : print_hex.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that takes a positive (or zero) number expressed in base 10,
and displays it in base 16 (lowercase letters) followed by a newline.

If the number of parameters is not 1, the program displays a newline.

Examples:

$> ./print_hex "10" | cat -e
a$
$> ./print_hex "255" | cat -e
ff$
$> ./print_hex "5156454" | cat -e
4eae66$
$> ./print_hex | cat -e
$
*/

#include <unistd.h>

int	ft_atoi(char *str)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (str[i])
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

void	ft_print_hex(int nb)
{
	char	*str_hex;

	str_hex = "0123456789abcdef";
	if (nb >= 16)
		ft_print_hex(nb / 16);
	write(1, &str_hex[nb % 16], 1);
}

int	main(int argc, char **argv)
{
	int	i;
	int	input;

	i = 0;
	input = 0;
	if (argc == 2)
	{
		input = ft_atoi(argv[1]);
		ft_print_hex(input);
	}
	write(1, "\n", 1);
	return (0);
}
