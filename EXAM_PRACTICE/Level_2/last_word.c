/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:52:12 by nkuydin           #+#    #+#             */
/*   Updated: 2025/11/06 18:12:58 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Assignment name  : last_word
Expected files   : last_word.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that takes a string and displays its last word followed by a \n.

A word is a section of string delimited by spaces/tabs or by the start/end of
the string.

If the number of parameters is not 1, or there are no words, display a newline.

Example:

$> ./last_word "FOR PONY" | cat -e
PONY$
$> ./last_word "this        ...       is sparta, then again, maybe    not"
not$
$> ./last_word "   " | cat -e
$
$> ./last_word "a" "b" | cat -e
$
$> ./last_word "  lorem,ipsum  " | cat -e
lorem,ipsum$
$>
*/

#include <unistd.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int	len;

	len = 0;
	if (argc == 2)
	{
		while (argv[1][len])
			len++;
		len--;
		while (argv[1][len] == ' ' || argv[1][len] == '\t')
			len--;
		while (!(argv[1][len] == ' ' || argv[1][len] == '\t'))
			len--;
		len++;
		while (argv[1][len] && !(argv[1][len] == ' ' || argv[1][len] == '\t'))
		{
			write(1, &argv[1][len], 1);
			len++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
