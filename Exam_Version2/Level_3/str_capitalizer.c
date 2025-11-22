/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_capitalizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 19:06:30 by nkuydin           #+#    #+#             */
/*   Updated: 2025/11/21 20:46:58 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Assignment name  : str_capitalizer
Expected files   : str_capitalizer.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that takes one or several strings and, for each argument,
capitalizes the first character of each word (If it's a letter, obviously),
puts the rest in lowercase, and displays the result on the standard output,
followed by a \n.

A "word" is defined as a part of a string delimited either by spaces/tabs, or
by the start/end of the string. If a word only has one letter, it must be
capitalized.

If there are no arguments, the progam must display \n.

Example:

$> ./str_capitalizer | cat -e
$
$> ./str_capitalizer "a FiRSt LiTTlE TESt" | cat -e
A First Little Test$
$> ./str_capitalizer "__SecONd teST A LITtle BiT   Moar comPLEX" "   But...
This iS not THAT COMPLEX" "     Okay, this is the last 1239809147801 but not   
the least    t" | cat -e
__second Test A Little Bit   Moar Complex$
   But... This Is Not That Complex$
     Okay, This Is The Last 1239809147801 But Not    The Least    T$
$>
*/

#include <unistd.h>

int	is_upper(char c)
{
	if ((c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	is_lower(char c)
{
	if ((c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

int	is_space(char c)
{
	if (c == 32 || c == '\t')
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	int	num;
	int	i;

	i = 0;
	num = 1;
	if (argc == 1)
	{
		write(1, "\n", 1);
		return (0);
	}
	while (num < argc)
	{
		while (argv[num][i])
		{
			if (is_upper(argv[num][i]))
				argv[num][i] += 32;
			if (is_lower(argv[num][i]) && is_space(argv[num][i - 1]))
				argv[num][i] -= 32;
			write(1, &argv[num][i], 1);
			i++;
		}
		write(1, "\n", 1);
		i = 0;
		num++;
	}
	return (0);
}
