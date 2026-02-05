/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:34:59 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/01/22 12:52:09 by Nikita_Kuyd      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i = 0;

	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int	s1_len = ft_strlen(s1);
	int	s2_len = ft_strlen(s2);
	int	i = 0;
	int	j = 0;
	char	*res;
	
	res = malloc(1 * (s1_len + s2_len + 1));
	if (!res)
		return (NULL);
	while (i < s1_len)
	{
		res[i] = s1[i];
		i++;
	}
	while (j < s2_len)
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	free(s1);
	return (res);
}

char	*ft_strchr(char *str, int c)
{
	int	i = 0;
	
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == c)
			return (str + i);
		i++;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char *stash;
	char		*buffer;
	int			bytes;
	char		*line;
	int			i;
	int			j;
	int			line_len;
	char		*new_stash;
	int			new_stash_len;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(1 * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes = 1;
	// read from fd //
	while (bytes > 0 && !ft_strchr(stash, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(buffer);
			return (NULL);
		}
		if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		stash = ft_strjoin(stash, buffer);
	}
	free(buffer);
	// extract line //
	i = 0;
	line_len = 0;
	if (!stash || stash[0] == '\0')
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	while (stash[i] && stash[i] != '\n')
		i++;
	line_len = i;
	if (stash[i] == '\n')
		line_len++;
	line = malloc(1 * (line_len + 1));
	if (!line)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	j = 0;
	while (j < line_len)
	{
		line[j] = stash[j];
		j++;
	}
	line[j] = '\0';
	// update storage //
	new_stash_len = 0;
	if (stash[line_len] != '\0')
	{
		while (stash[line_len + new_stash_len] != '\0')
			new_stash_len++;
		new_stash = malloc(1 * (new_stash_len + 1));
		if (!new_stash)
		{
			free(stash);
			stash = NULL;
			return (NULL);
		}
		j = 0;
		while (j < new_stash_len)
		{
			new_stash[j] = stash[line_len + j];
			j++;
		}
		new_stash[j] = '\0';
		free(stash);
		stash = new_stash;
	}
	else
	{
		free(stash);
		stash = NULL;
	}
	return (line);
}

int	main(void)
{
	int 	fd;
	char	*line;
	int		i = 0;
	
	fd = open("file.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		i++;
		printf("Line number: %d; Line: %s", i, line);
		free(line);
		line = get_next_line(fd);
	}
}
