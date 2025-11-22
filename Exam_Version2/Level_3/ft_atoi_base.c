/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 00:50:44 by nkuydin           #+#    #+#             */
/*   Updated: 2025/11/22 02:36:30 by nkuydin          ###   ########.fr       */
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
	int		i;
	char	*upper;
	char	*lower;

	i = 0;
	upper = "0123456789ABCDEF";
	lower = "0123456789abcdef";
	while (i < base)
	{
		if (c == upper[i] || c == lower[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi_base(const char *str, int str_base)
{
	int	sign;
	int	result;
	int	i;

	i = 0;
	sign = 1;
	result = 0;
	if (str_base <= 16)
	{
		if (str[i] == '-')
		{
			sign *= -1;
			i++;
		}
		while (str[i] && is_valid(str[i], str_base))
		{
			if (str[i] >= '0' && str[i] <= '9')
				result = result * str_base + (str[i] - '0');
			else if (str[i] >= 'a' && str[i] <= 'f')
				result = result * str_base + (str[i] - 'a') + 10;
			else if (str[i] >= 'A' && str[i] <= 'F')
				result = result * str_base + (str[i] - 'A') + 10;
			i++;
		}
	}
	result *= sign;
	return (result);
}

int	main(void)
{
	int	res;

	res = ft_atoi_base("1f", 16);
	printf("%i", res);
}
