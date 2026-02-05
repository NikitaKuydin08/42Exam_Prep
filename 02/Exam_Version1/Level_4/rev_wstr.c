/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_wstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:05:49 by nkuydin           #+#    #+#             */
/*   Updated: 2025/11/18 17:36:01 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Assignment name  : rev_wstr
Expected files   : rev_wstr.c
Allowed functions: write, malloc, free
--------------------------------------------------------------------------------

Write a program that takes a string as a parameter, and prints its words in
reverse order.

A "word" is a part of the string bounded by spaces and/or tabs, or the
begin/end of the string.

If the number of parameters is different from 1, the program will display
'\n'.

In the parameters that are going to be tested, there won't be any "additional"
spaces (meaning that there won't be additionnal spaces at the beginning or at
the end of the string, and words will always be separated by exactly one space).

Examples:

$> ./rev_wstr "You hate people! But I love gatherings. Isn't it ironic?" | cat -e
ironic? it Isn't gatherings. love I But people! hate You$
$>./rev_wstr "abcdefghijklm"
abcdefghijklm
$> ./rev_wstr "Wingardium Leviosa" | cat -e
Leviosa Wingardium$
$> ./rev_wstr | cat -e
$
$>
*/

#include <unistd.h>

int	main(int argc, char **argv)
{
	int	i;
	int	j;
	int	not_first_word;

	i = 0;
	j = 0;
	not_first_word = 0;
	if (argc == 2)
	{
		while (argv[1][i])
			i++;
		i--;
		while (i-- > 0)
		{
			while (i >= 0 && (argv[1][i] == ' ' || argv[1][i] == '\t'))
				i--;
			j = i;
			while (j >= 0 && argv[1][j] != ' ' && argv[1][j] != '\t')
				j--;
			if (not_first_word)
				write(1, " ", 1);
			write(1, &argv[1][j + 1], i - j);
			not_first_word = 1;
			i = j;
		}
	}
	write(1, "\n", 1);
	return (0);
}
