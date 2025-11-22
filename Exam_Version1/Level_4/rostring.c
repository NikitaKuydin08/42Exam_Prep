/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rostring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:01:32 by nkuydin           #+#    #+#             */
/*   Updated: 2025/11/19 23:17:42 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Assignment name  : rostring
Expected files   : rostring.c
Allowed functions: write, malloc, free
--------------------------------------------------------------------------------

Write a program that takes a string and displays this string after rotating it
one word to the left.

Thus, the first word becomes the last, and others stay in the same order.

A "word" is defined as a part of a string delimited either by spaces/tabs, or
by the start/end of the string.

Words will be separated by only one space in the output.

If there's less than one argument, the program displays \n.

Example:

$>./rostring "abc   " | cat -e
abc$
$>
$>./rostring "Que la      lumiere soit et la lumiere fut"
la lumiere soit et la lumiere fut Que
$>
$>./rostring "     AkjhZ zLKIJz , 23y"
zLKIJz , 23y AkjhZ
$>
$>./rostring "first" "2" "11000000"
first
$>
$>./rostring | cat -e
$
$>
*/

#include <stdlib.h>
#include <unistd.h>

int	is_skip(char c)
{
	if (c <= 32)
		return (1);
	return (0);

}

int	main(int argc, char **argv)
{
	char	*str;
	int		i;
	int		j;
	int		end;
	int		start;

	i = 0;
	j = 0;
	start = 0;
	end = 0;
	str = argv[1];
	if (argc >= 2)
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		start = i;
		while (str[i] && str[i] != ' ' && str[i] != '\t')
			i++;
		end = i - start;
		while (str[i])
		{
			if ()
		}
	}
	write(1, "\n", 1);
	return (0);
}
