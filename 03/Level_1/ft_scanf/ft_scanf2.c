/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scanf2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 16:17:10 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/02/08 01:04:48 by Nikita_Kuyd      ###   ########.fr       */
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
    int ch;
    int valid = 0;

    ch = fgetc(f);
    if (ch == '-')
    {
        sign *= -1;
        ch = fgetc(f);
    }
    if (ch == '+')
        ch = fgetc(f);
    if (!isdigit(ch))
    {
        if (ch != EOF)
            ungetc(ch, f);
        return (-1);
    }
    while (ch != EOF && isdigit(ch))
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
    while (ch != EOF && !isspace(ch))
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


int	match_conv(FILE *f, const char *c, va_list *ap)
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
			if (match_conv(f, &format[++i], &ap) == -1)
				break;
			else
				nconv++;
		}
		else if (isspace(format[i]))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, format[i]) == -1)
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
    
    va_start(ap, format);
	int result = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return (result);
}

int main(void)
{
    int dig;
    char    c;
    char    str[50];

    int result = ft_scanf("%d %s %c", &dig, str, &c);
    printf("Result: %d\ndigit: %d\nstring: %s\nchar: %c", result, dig, str, c);
}