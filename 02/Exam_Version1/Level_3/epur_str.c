/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epur_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:44:42 by nkuydin           #+#    #+#             */
/*   Updated: 2025/11/07 16:30:58 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Assignment name  : epur_str
Expected files   : epur_str.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that takes a string, and displays this string with exactly one
space between words, with no spaces or tabs either at the beginning or the end,
followed by a \n.

A "word" is defined as a part of a string delimited either by spaces/tabs, or
by the start/end of the string.

If the number of arguments is not 1, or if there are no words to display, the
program displays \n.

Example:

$> ./epur_str "vous voyez c'est facile d'afficher la meme chose" | cat -e
vous voyez c'est facile d'afficher la meme chose$
$> ./epur_str " seulement          la c'est      plus dur " | cat -e
seulement la c'est plus dur$
$> ./epur_str "comme c'est cocasse" "vous avez entendu, Mathilde ?" | cat -e
$
$> ./epur_str "" | cat -e
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
	int		i;
	int		space;

	i = 0;
	space = 0;
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
					write(1, " ", 1);
				space = 0;
				write(1, &argv[1][i], 1);
			}
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
