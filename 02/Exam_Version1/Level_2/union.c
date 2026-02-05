/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:26:39 by nkuydin           #+#    #+#             */
/*   Updated: 2025/11/06 17:06:37 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Assignment name  : union
Expected files   : union.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that takes two strings and displays, without doubles, the
characters that appear in either one of the strings.

The display will be in the order characters appear in the command line, and
will be followed by a \n.

If the number of arguments is not 2, the program displays \n.

Example:

$>./union zpadinton "paqefwtdjetyiytjneytjoeyjnejeyj" | cat -e
zpadintoqefwjy$
$>./union ddf6vewg64f gtwthgdwthdwfteewhrtag6h4ffdhsd | cat -e
df6vewg4thras$
$>./union "rien" "cette phrase ne cache rien" | cat -e
rienct phas$
$>./union | cat -e
$
$>
$>./union "rien" | cat -e
$
$>
*/

#include <unistd.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

int	main(int argc, char **argv)
{
	int		i;
	int		len;
	int		j;
	int		unique;

	i = 0;
	len = 0;
	j = 0;
	if (argc == 3)
	{
		len = ft_strlen(argv[1]); // total length of concatenated string
		while (argv[2][i]) // strcat
		{
			argv[1][len] = argv[2][i];
			len++;
			i++;
		}
		len--;
		while (j <= len)
		{
			// current character we’re checking:
			// argv[1][j]
			i = 0;
			unique = 1;
			while (i < j)
			{
				// Step 4: check all characters *before* j (current char)
				// if any of them equals the current character,
				// mark it as duplicate (unique = 0)
				if (argv[1][i] == argv[1][j])
					unique = 0;
				i++;
			}
			if (unique)
				write(1, &argv[1][j], 1);
			j++;
		}
	}
	write(1, "\n", 1);
	return (0);
}


// j <= len - for the length of the whole concatenate string
// i < j - check the character that have alredy been written, so for
// example j = 0 initially it means that we write a charcter, than
// next iteration j = 1, it means that we checking one
// character before the current one, make sure that they are not the same