/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   practice.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:43:11 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/02/05 13:00:46 by Nikita_Kuyd      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int main(void)
{
    int     dig;
    char    c;
    char    str[50];

    int result = scanf("%d %c %s", &dig, &c, str);
    printf("Result: %d\nDigit: %d\nChar: %c\nString: %s", result, dig, c, str);
}

// scanf skips all consecutive spaces, then otputs the string until there are spaces for %s
// scanf skips all consecutive spaces, stores the number inside of the variable, utill there is a character different from the digit for %d
// scanf takes the first character inputed no matter of the type, and stores it inside of variable.

//RETURN_VALUE: The scanf function returns the number of items successfully read and assigned to variables.

// If the input does not match the format string at all (e.g., user types "abc" when you asked for %d), it returns 0

// It returns EOF (typically defined as -1) if it encounters the "End of File" or a read error before any data could be read.

// match_char is used to enforce literal characters in the format string so that the input must match the format exactly, just like in standard scanf.
// ft_scanf("(%d,%d)", &x, &y);
// intended input: (10,20)

// for the integer we get va_args(ap, int *);
// for the char/string we get va_args(ap, char *);


// first we take one character, after we check if it is eof if true return -1
// then, skip leading spaces, whiel isspace -> true, get a character
// if character == '-', then sign = -1. take another character
// else if character equals '+', take anther character
// if it's not digit after the sign, ungetc(ch, stream), return -1
// while ch is still isdigit, do value = value * 10 + (ch - '0');
// count++;
// get another character
// if (ch != EOF) --> ungetc(ch, strem)