/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:22:49 by nkuydin           #+#    #+#             */
/*   Updated: 2025/11/06 17:05:09 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Assignment name  : inter
Expected files   : inter.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that takes two strings and displays, without doubles, the
characters that appear in both strings, in the order they appear in the first
one.

The display will be followed by a \n.

If the number of arguments is not 2, the program displays \n.

Examples:

$>./inter "padinton" "paqefwtdjetyiytjneytjoeyjnejeyj" | cat -e
padinto$
$>./inter ddf6vewg64f gtwthgdwthdwfteewhrtag6h4ffdhsd | cat -e
df6ewg4$
$>./inter "rien" "cette phrase ne cache rien" | cat -e
rien$
$>./inter | cat -e
$
*/

#include <unistd.h>

int	main(int argc, char **argv)
{
	int	len;
	int	i;
	int	j;
	int	unique;
	int	allow;

	len = 0;
	i = 0;
	if (argc == 3)
	{
		while (argv[1][i])
		{
			unique = 1;
			j = 0;
			allow = 0;
			while (j < i)
			{
				if (argv[1][i] == argv[1][j])
					unique = 0;
				j++;
			}
			j = 0;
			while (argv[2][j])
			{
				if (argv[1][i] == argv[2][j])
					allow = 1;
				j++;
			}
			if (unique && allow)
				write(1, &argv[1][i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
