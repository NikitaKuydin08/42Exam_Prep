/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scanf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:46:18 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/02/07 12:37:19 by Nikita_Kuyd      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <ctype.h>

// fgetc, ungetc, ferror, feof, isspace, isdigit, stdin, va_start, va_arg, va_copy, va_end

int ft_vfscanf(FILE *stream, const char *format, va_list ap);

int ft_scanf(const char *format, ...)
{
    va_list ap;
    int     result;

    va_start(ap, format);
    result = ft_vfscanf(stdin, format, ap);
    va_end(ap);
    return (result);
}

int skip_space(FILE *stream)
{
    /*
     * WHITESPACE HANDLING:
     * - Read characters while they are whitespace
     * - Push back the first non-whitespace character to the stream
     * - Return -1 on error
     */
    int ch;
    
    while ((ch = fgetc(stream)) != EOF)
    {
        if (!isspace(ch))
        {
            ungetc(ch, stream);
            break ;
        }
    }
    if (ferror(stream))
        return (-1);
    return (0);
}

int match_char(FILE *stream, char c)
{
    /*
     * LITERAL CHARACTER MATCHING:
     * - Read one character from the stream
     * - Check if it matches the expected one
     * - Push it back if it does not match
     */
    int ch;

    ch = fgetc(stream);
    if (ch == c)
        return (0);
    if (ch != EOF)
        ungetc(ch, stream);
    return (-1);
}

int scan_char(FILE *stream, va_list *ap)
{
    int ch;

    ch = fgetc(stream);
    if (ch == EOF)
        return (-1);
    char *cp = va_arg(*ap, char *);
    *cp = (char)ch;
    return (0);
}

int scan_int(FILE *stream, va_list *ap)
{
    int ch;
    int *ip = va_arg(*ap, int *);;
    int sign = 1;
    int value = 0;
    int count = 0;

    ch = fgetc(stream);
    if (ch == EOF)
        return (-1);
    if (ch == '-')
    {
        sign = -1;
        ch = fgetc(stream);
    }
    else if (ch == '+')
    {
        ch = fgetc(stream);
    }
    if (!isdigit(ch))
    {
        ungetc(ch, stream);
        return (-1);
    }
    while (isdigit(ch))
    {
        value = value * 10 + (ch - '0');
        count++;
        ch = fgetc(stream);
    }
    if (ch != EOF)
        ungetc(ch, stream);
    if (count == 0)
        return (-1);
    *ip = value * sign;
    return (0);
}

int scan_string(FILE *stream, va_list *ap)
{
    int     ch;
    int     i = 0;
    char    *sp = va_arg(*ap, char *);
    
    ch = fgetc(stream);
    while (ch != EOF && !isspace(ch))
    {
        sp[i] = ch;
        i++;
        ch = fgetc(stream);
    }
    sp[i] = '\0';
    if (ch != EOF)
        ungetc(ch, stream);
    if (i == 0)
        return (-1);
    return (0);
}

int match_conv(FILE *stream, const char *c, va_list *ap)
{
    if (*c == 'c')
        return (scan_char(stream, ap));
    else if (*c == 'd')
    {
        skip_space(stream);
        return (scan_int(stream, ap));
    }
    else if (*c == 's')
    {
        skip_space(stream);
        return (scan_string(stream, ap));
    }
    else if (*c == EOF)
        return (-1);
    else
        return (-1);
}

int ft_vfscanf(FILE *stream, const char *format, va_list ap)
{
    int nsuccess;
    int ch;
    int i;

    nsuccess = 0;
    i = 0;
    ch = fgetc(stream);
    if (ch == EOF)
        return (EOF);
    ungetc(ch, stream);
    while (format[i])
    {
        if (format[i] == '%')
        {
            if (match_conv(stream, &format[++i], &ap) != 0)
                break ;
            else
                nsuccess++;
        }
        else if (isspace(format[i]))
        {
            if (skip_space(stream) == -1)
                break ;
        }
        else if (match_char(stream, format[i]) != 0)
            break ;
        i++;
    }
    if (ferror(stream))
        return (EOF);
    return (nsuccess);
}

int main(void)
{
    int     dig;
    char    c;
    char    str[50];

    int result = ft_scanf("%d %c %s", &dig, &c, str);
    printf("Result: %d\nDigit: %d\nChar: %c\nString: %s", result, dig, c, str);
}
