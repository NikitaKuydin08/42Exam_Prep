/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:05:51 by nkuydin           #+#    #+#             */
/*   Updated: 2025/10/11 14:16:08 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/*
Assignment name  : rev_print
Expected files   : rev_print.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that takes a string, and displays the string in reverse
followed by a newline.

If the number of parameters is not 1, the program displays a newline.

Examples:

$> ./rev_print "zaz" | cat -e
zaz$
$> ./rev_print "dub0 a POIL" | cat -e
LIOP a 0bud$
$> ./rev_print | cat -e
$
*/

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

// int	main(int argc, char **argv)
// {
// 	int	i;

// 	i = 0;
// 	if (argc == 2)
// 	{
// 		while (argv[1][i])
// 			i++;
// 		while (i > 0)
// 		{
// 			i--;
// 			write(1, &argv[1][i], 1);
// 		}
// 	}
// 	write(1, "\n", 1);
// }

char	*rev_print(char *str)
{
	int	i;

	i = ft_strlen(str);
	while (str[--i])
		write(1, &str[i], 1);
	return (str);
}

int	main(void)
{
	rev_print("Hello World");
	write(1, "\n", 1);
	rev_print("revers print");
	write(1, "\n", 1);
	return (0);
}
