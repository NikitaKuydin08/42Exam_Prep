/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_scanf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:23:35 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/02/08 15:08:59 by Nikita_Kuyd      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
    int ch;

    while ((ch = fgetc(f)) != EOF)
    {
        if (!isspace((unsigned char)ch))
        {
            ungetc(ch, f);
            return (0);
        }
    }
    if (ferror(f))
        return (-1);
    return (0);
}

int match_char(FILE *f, char c)
{
    int ch;

    ch = fgetc(f);
    if (ch == c)
        return (0);
    if (ch != EOF)
        ungetc(ch, f);
    return (-1);
}

int scan_char(FILE *f, va_list *ap)
{
    char    *c = va_arg(*ap, char *);
    int     ch;

    ch = fgetc(f);
    if (ch == EOF)
        return (-1);
    *c = (char)ch;
    return (0);
}

int scan_int(FILE *f, va_list *ap)
{
    int *dig = va_arg(*ap, int *);
    int value = 0;
    int sign = 1;
    int valid = 0;
    int ch;
    
    ch = fgetc(f);
    if (ch == EOF)
        return (-1);
    if (ch == '-')
    {
        sign *= -1;
        ch = fgetc(f);
    }
    if (ch == '+')
        ch = fgetc(f);
    if (!isdigit((unsigned char)ch))
    {
        ungetc(ch, f);
        return (-1);
    }
    while (ch != EOF && isdigit((unsigned char)ch))
    {
        valid = 1;
        value = value * 10 + (ch - '0');
        ch = fgetc(f);
    }
    if (ch != EOF)
        ungetc(ch, f);
    if (!valid)
        return (-1);
    *dig = value * sign;
    return (0);
}

int scan_string(FILE *f, va_list *ap)
{
    char    *str = va_arg(*ap, char *);
    int     i = 0;
    int     ch;

    ch = fgetc(f);
    if (ch == EOF)
        return (-1);
    while (ch != EOF && !isspace((unsigned char)ch))
    {
        str[i] = (char)ch;
        ch = fgetc(f);
        i++;
    }
    str[i] = '\0';
    if (ch != EOF)
        ungetc(ch, f);
    if (i == 0)
        return (-1);
    return (0);
}

int match_conv(FILE *f, const char *c, va_list *ap)
{
    if (*c == 'c')
        return (scan_char(f, ap));
    else if (*c == 'd')
    {
        match_space(f);
        return (scan_int(f, ap));
    }
    else if (*c == 's')
    {
        match_space(f);
        return (scan_string(f, ap));
    }
    else
        return (-1);
}

int ft_vfscanf(FILE *f, const char *format, va_list *ap)
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
			if (match_conv(f, &format[++i], ap) == -1)
				break ;
			else
				nconv++;
		}
		else if (isspace((unsigned char)format[i]))
		{
			if (match_space(f) == -1)
				break ;
		}
		else if (match_char(f, format[i]) == -1)
			break ;
		i++;
	}
	
	if (ferror(f))
		return (EOF);
	return (nconv);
}


int ft_scanf(const char *format, ...)
{
	va_list ap;

    va_start(ap, format);
	int result = ft_vfscanf(stdin, format, &ap);
	va_end(ap);
	return (result);
}
