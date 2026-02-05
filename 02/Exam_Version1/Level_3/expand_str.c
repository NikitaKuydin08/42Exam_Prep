/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:32:24 by nkuydin           #+#    #+#             */
/*   Updated: 2025/11/07 16:40:50 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Assignment name  : expand_str
Expected files   : expand_str.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that takes a string and displays it with exactly three spaces
between each word, with no spaces or tabs either at the beginning or the end,
followed by a newline.

A word is a section of string delimited either by spaces/tabs, or by the
start/end of the string.

If the number of parameters is not 1, or if there are no words, simply display
a newline.

Examples:

$> ./expand_str "vous   voyez   c'est   facile   d'afficher   la   meme   chose" | cat -e
vous   voyez   c'est   facile   d'afficher   la   meme   chose$
$> ./expand_str " seulement          la c'est      plus dur " | cat -e
seulement   la   c'est   plus   dur$
$> ./expand_str "comme c'est cocasse" "vous avez entendu, Mathilde ?" | cat -e
$
$> ./expand_str "" | cat -e
$
$>
*/

#include <unistd.h>

int	is_skip(char c)
{
	if (c <= 32)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	int	i;
	int	space;

	space = 0;
	i = 0;
	if (argc == 2 && argv[1][0] != '\0')
	{
		while (is_skip(argv[1][i]))
			i++;
		while (argv[1][i])
		{
			if (is_skip(argv[1][i]))
				space = 1;
			if (!is_skip(argv[1][i]))
			{
				if (space)
					write(1, "   ", 3);
				space = 0;
				write(1, &argv[1][i], 1);
			}
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
