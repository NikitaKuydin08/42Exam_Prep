/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:41:28 by nkuydin           #+#    #+#             */
/*   Updated: 2025/11/22 02:54:37 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Assignment name  : ft_atoi_base
Expected files   : ft_atoi_base.c
Allowed functions: None
--------------------------------------------------------------------------------

Write a function that converts the string argument str (base N <= 16)
to an integer (base 10) and returns it.

The characters recognized in the input are: 0123456789abcdef
Those are, of course, to be trimmed according to the requested base. For
example, base 4 recognizes "0123" and base 16 recognizes "0123456789abcdef".

Uppercase letters must also be recognized: "12fdb3" is the same as "12FDB3".

Minus signs ('-') are interpreted only if they are the first character of the
string.

Your function must be declared as follows:

int	ft_atoi_base(const char *str, int str_base);
*/

#include <stdio.h>

int	is_valid(char c, int base)
{
	
}

int	ft_atoi_base(const char *str, int str_base)
{
	int	sign;
	int	i;
	int	result;

	sign = 1;
	i = 0;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			result = result * str_base + (str[i] - '0');
		else if (str[i] >= 'a' && str[i] <= 'f')
			result = result * str_base + (str[i] - 'a') + 10;
		else if (str[i] >= 'A' && str[i] <= 'F')
			result = result * str_base + (str[i] - 'A') + 10;
		i++;
	}
	result *= sign;
	return (result);
}

int main(void)
{
    printf("%d\n", ft_atoi_base("42", 10));           // 42
    printf("%d\n", ft_atoi_base("-42", 10));          // -42
    printf("%d\n", ft_atoi_base("000101", 2));        // 5
    printf("%d\n", ft_atoi_base("-101", 2));          // -5
    printf("%d\n", ft_atoi_base("777", 8));           // 511
    printf("%d\n", ft_atoi_base("ABC", 16));          // 2748
    printf("%d\n", ft_atoi_base("abc", 16));          // 2748
    printf("%d\n", ft_atoi_base("12fdb3", 16));       // 1244595

    printf("%d\n", ft_atoi_base("1012", 2));          // 5
    printf("%d\n", ft_atoi_base("19", 8));            // 1
    printf("%d\n", ft_atoi_base("1fZ3", 16));         // 31
    printf("%d\n", ft_atoi_base("3A7", 11));          // 373
    printf("%d\n", ft_atoi_base("3B7", 11));          // 3

    printf("%d\n", ft_atoi_base("-123", 4));          // -27
    printf("%d\n", ft_atoi_base("1-23", 4));          // 1

    printf("%d\n", ft_atoi_base("0", 2));             // 0
    printf("%d\n", ft_atoi_base("-0", 10));           // 0
    printf("%d\n", ft_atoi_base("", 10));             // 0
    printf("%d\n", ft_atoi_base("G", 16));            // 0
    printf("%d\n", ft_atoi_base("f", 15));            // 0

    printf("%d\n", ft_atoi_base("101", 1));           // 0
    printf("%d\n", ft_atoi_base("FF", 17));           // 0
}
