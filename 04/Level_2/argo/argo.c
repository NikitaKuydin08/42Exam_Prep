#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef struct	json {
	enum {
		MAP,
		INTEGER,
		STRING
	} type;
	union {
		struct {
			struct pair	*data;
			size_t		size;
		} map;
		int	integer;
		char	*string;
	};
}	json;

typedef struct	pair {
	char	*key;
	json	value;
}	pair;

void	free_json(json j);
int parse_integer(json *dst, FILE *stream);
int parse_string(json *dst, FILE *stream);
int parse_map(json *dst, FILE *stream);

int	peek(FILE *stream)
{
	int	c = getc(stream);
	ungetc(c, stream);
	return c;
}

void	unexpected(FILE *stream)
{
	if (peek(stream) != EOF)
		printf("unexpected token '%c'\n", peek(stream));
	else
		printf("unexpected end of input\n");
}

int	accept(FILE *stream, char c)
{
	if (peek(stream) == c)
	{
		(void)getc(stream);
		return 1;
	}
	return 0;
}

int	expect(FILE *stream, char c)
{
	if (accept(stream, c))
		return 1;
	unexpected(stream);
	return 0;
}

int parse_value(json *dst, FILE *stream)
{
	int	ch;

	ch = peek(stream);
	if (isdigit(ch) != 0 || ch == '-' || ch == '+')
		return (parse_integer(dst, stream));
	else if (ch == '"')
		return (parse_string(dst, stream));
	else if (ch == '{')
		return (parse_map(dst, stream));
	else
	{
		unexpected(stream);
		return (-1);
	}
}

int parse_integer(json *dst, FILE *stream)
{
	if (fscanf(stream, "%d", &dst->integer) != 1)
		return (-1);
	dst->type = INTEGER;
	return (1);
}

int parse_string(json *dst, FILE *stream)
{
	char    *buffer;
	size_t  len_buf;
	int		ch;
	int		next_ch;

	len_buf = 0;
	if (expect(stream, '"') != 1)
		return (-1);
	ch = getc(stream);
	buffer = NULL;
	while (ch != EOF)
	{
		buffer = realloc(buffer, len_buf + 2);
		if (!buffer)
			return (-1);
		if (ch == '\\')
		{
			next_ch = getc(stream);
			if (next_ch == EOF)
			{
				printf("Unexpected end of input\n");
				if (buffer)
					free(buffer);
				return (-1);
			}
			if (next_ch == '"' || next_ch == '\\')
				buffer[len_buf] = next_ch;
		}
		else if (ch == '"')
			break ;
		else
			buffer[len_buf] = ch;
		ch = getc(stream);
		len_buf++;
	}
	if (ch == EOF)
	{
		printf("Unexpected end of input\n");
		if (buffer)
			free(buffer);
		return (-1);
	}
	buffer[len_buf] = '\0';
	dst->type = STRING;
	dst->string = buffer;
	return (1);
}

int parse_map(json *dst, FILE *stream)
{
	json	copy_dst;

	if (expect(stream, '{') != 1)
		return (-1);
	dst->type = MAP;
	dst->map.data = NULL;
	dst->map.size = 0;

	if (accept(stream, '}') == 1)
		return (1);
	while (1)
	{
		dst->map.data = realloc(dst->map.data, sizeof(pair) * (dst->map.size + 1));
		if (parse_string(&copy_dst, stream) != 1)
		{
			free_json(*dst);
			return (-1);
		}
		dst->map.data[dst->map.size].key = copy_dst.string;
		if (expect(stream, ':') != 1)
		{
			free_json(*dst);
			return (-1);
		}
		if (parse_value(&dst->map.data[dst->map.size].value, stream) != 1)
		{
			free_json(*dst);
			return (-1);
		}
		dst->map.size++;
		if (accept(stream, ',') != 1)
			break ;
	}
	if (expect(stream, '}') != 1)
		return (-1);
	return (1);
}

int	argo(json *dst, FILE *stream)
{
	if (parse_value(dst, stream) != 1)
		return (-1);
	return (1);
}


void	free_json(json j)
{
	if (j.type)
	{
		switch (j.type)
		{
			case MAP:
				for (size_t i = 0; i < j.map.size; i++)
				{
					free(j.map.data[i].key);
					free_json(j.map.data[i].value);
				}
				free(j.map.data);
				break ;
			case STRING:
				free(j.string);
				break ;
			default:
				break ;
		}
	}
}
/*
void	serialize(json j)
{
	switch (j.type)
	{
		case INTEGER:
			printf("%d", j.integer);
			break ;
		case STRING:
			putchar('"');
			for (int i = 0; j.string[i]; i++)
			{
				if (j.string[i] == '\\' || j.string[i] == '"')
					putchar('\\');
				putchar(j.string[i]);
			}
			putchar('"');
			break ;
		case MAP:
			putchar('{');
			for (size_t i = 0; i < j.map.size; i++)
			{
				if (i != 0)
					putchar(',');
				serialize((json){.type = STRING, .string = j.map.data[i].key});
				putchar(':');
				serialize(j.map.data[i].value);
			}
			putchar('}');
			break ;
	}
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return 1;
	char *filename = argv[1];
	FILE *stream = fopen(filename, "r");
	json	file;
	if (argo (&file, stream) != 1)
	{
		free_json(file);
		return 1;
	}
	serialize(file);
	printf("\n");
}
*/