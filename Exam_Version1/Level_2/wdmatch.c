/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wdmatch.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 19:41:22 by nkuydin           #+#    #+#             */
/*   Updated: 2025/11/06 20:21:14 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Assignment name  : wdmatch
Expected files   : wdmatch.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that takes two strings and checks whether it's possible to
write the first string with characters from the second string, while respecting
the order in which these characters appear in the second string.

If it's possible, the program displays the string, followed by a \n, otherwise
it simply displays a \n.

If the number of arguments is not 2, the program displays a \n.

Examples:

$>./wdmatch "faya" "fgvvfdxcacpolhyghbreda" | cat -e
faya$
$>./wdmatch "faya" "fgvvfdxcacpolhyghbred" | cat -e
$
$>./wdmatch "quarante deux" "qfqfsudf arzgsayns tsregfdgs sjytdekuoixq " | cat -e
quarante deux$
$>./wdmatch "error" rrerrrfiiljdfxjyuifrrvcoojh | cat -e
$
$>./wdmatch | cat -e
$
*/

#include <unistd.h>

size_t	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	main(int argc, char **argv)
{
	int	i;
	int	j;
	int	allow;

	i = 0;
	j = 0;
	if (argc == 3)
	{
		while (argv[1][i])
		{
			allow = 0;
			while (argv[2][j])
			{
				if (argv[1][i] == argv[2][j])
				{
					allow = 1;
					break ;
				}
				j++;
			}
			i++;
		}
		if (allow)
			write(1, argv[1], ft_strlen(argv[1]));
	}
	write(1, "\n", 1);
	return (0);
}

// int	main(int argc, char **argv)
// {
// 	int	i;
// 	int	j;
// 	int	len;

// 	i = 0;
// 	j = 0;
// 	len = 0;
// 	if (argc == 3)
// 	{
// 		while (argv[1][len])
// 			len++;
// 		while (i < len && argv[2][j])
// 		{
// 			if (argv[1][i] == argv[2][j])
// 				i++;
// 			j++;
// 		}
// 		if (i == len)
// 			write(1, argv[1], len);
// 	}
// 	write(1, "\n", 1);
// 	return (0);
// }
