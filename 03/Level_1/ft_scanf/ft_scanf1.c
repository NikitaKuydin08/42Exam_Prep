/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scanf1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 17:31:10 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/02/05 17:46:05 by Nikita_Kuyd      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int    match_space(FILE *f)
{
    char    ch;

    while ((ch = fgetc(f)) != EOF)
    {
        if (!isspace(ch))
        {
            ungetc(ch, f);
            break ;
        }
    }
    if (ferror(f))
        return (-1);
    return (0);
}

int	match_conv(FILE *f, char *c, va_list ap)
{
	switch (*c)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;
    int i = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (format[i])
	{
		if (format[i] == '%')
		{
			if (match_conv(f, &format[++i], ap) != 1)
				break;
			else
				nconv++;
		}
		else if (isspace(format[i]))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, format[i]) != 1)
			break;
		i++;
	}
	
	if (ferror(f))
		return EOF;
	return nconv;
}

int ft_scanf(const char *format, ...)
{
    va_list ap;
    int     result;
	
    va_start(ap, format);
	result = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return (result);
}
