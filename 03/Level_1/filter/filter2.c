#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1

int	error(void)
{
	perror("Error");
	return (1);
}

int main(int argc, char **argv)
{
	char	*buffer;
	int		bytes;
	char	*pattern;
	int		pattern_len;
	char	*stash;
	int		stash_len;
	int		i;
	int		j;
	char	*temp;
	char	*match;
	int		before_match;

	if (argc != 2 || argv[1][0] == '\0')
		return (1);
	buffer = malloc(1 * (BUFFER_SIZE));
	if (!buffer)
		return (error());
	temp = NULL;
	stash = NULL;
	stash_len = 0;
	pattern = argv[1];
	pattern_len = strlen(pattern);
	while (1)
	{
		bytes = read(0, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (error());
		if (bytes == 0)
			break ;
		temp = realloc(stash, bytes + stash_len);
		if (!temp)
			return (error());
		stash = temp;
		memmove(stash + stash_len, buffer, bytes);
		stash_len += bytes;
		i = 0;
		while ((match = memmem(stash + i, stash_len - i, pattern, pattern_len)))
		{
			before_match = match - (stash - i);
			write(1, stash + i, before_match);
			for (j = 0; j < pattern_len; j++)
				write(1, "*", 1);
			i += before_match + pattern_len;
		}
		if (i > 0)
		{
			memmove(stash, stash + i, stash_len - i);
			stash_len -= i;
			temp = realloc(stash, stash_len);
			if (!temp && stash_len > 0)
				return (error());
			stash = temp;
		}
	}
	if (stash_len > 0)
		write(1, stash, stash_len);
	free(stash);
	return (0);
}
