/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:02:17 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/02/05 16:50:48 by Nikita_Kuyd      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

int	error_mes(void)
{
	perror("Error");
	return (1);
}

int main(int argc, char **argv)
{
	char    *pattern;
	int		pattern_len;
	int     i;
	int		j;
	char	*buffer;
	int		bytes;
	char	*stash;
	int		stash_len;
	char	*temp;
	char	*match;
	int		before_match;

	if (argc != 2 || argv[1][0] == '\0')
		return (1);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (error_mes());
	pattern = argv[1];
	pattern_len = strlen(pattern);
	stash = NULL;
	stash_len = 0;
	while (1)
	{
		bytes = read(0, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (error_mes());
		if (bytes == 0)
			break ;
		temp = realloc(stash, stash_len + bytes);
		if (!temp)
			return (error_mes());
		stash = temp;
		memmove(stash + stash_len, buffer, bytes);
		stash_len += bytes;
		i = 0;
		while ((match = memmem(stash + i, stash_len - i, pattern, pattern_len)))
		{
			before_match = match - (stash + i);
			write(1, stash + i, before_match); // right
			// for(j = 0; j < before_match; j++) // wrong, from exam
			// 	write(1, stash + i, 1);
			j = 0;
			while (j < pattern_len)
			{
				write(1, "*", 1);
				j++;
			}
			i += before_match + pattern_len;
		}
		if (i > 0)
		{
			memmove(stash, stash + i, stash_len - i);
			stash_len -= i;
			temp = realloc(stash, stash_len);
			if (!temp && stash_len > 0)
				return (error_mes());
			stash = temp;
		}
	}
	if (stash_len > 0)
		write(1, stash, stash_len);
	free(stash);
	return (0);
}
