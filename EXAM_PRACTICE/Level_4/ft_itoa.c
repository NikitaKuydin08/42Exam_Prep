/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:10:04 by nkuydin           #+#    #+#             */
/*   Updated: 2025/11/14 19:10:04 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Assignment name  : ft_itoa
Expected files   : ft_itoa.c
Allowed functions: malloc
--------------------------------------------------------------------------------

Write a function that takes an int and converts it to a null-terminated string.
The function returns the result in a char array that you must allocate.

Your function must be declared as follows:

char	*ft_itoa(int nbr);

*/

#include <stdlib.h>

int	count(int nb)
{
	int	count;

	count = 0;
	if (nb < 0)
		count++;
	while (nb >= 0)
	{
		nb /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int nbr)
{
	int		len;
	char	*res;
	int		i;

	i = 0;
	len = count(nbr);
	res = malloc(sizeof(char) * (len + 1));
	if (nbr < 0)
	{
		res[i] = '-';
		nbr *= -1;
		i++;
	}
	while (nbr >= 0)
	{
		
	}
}
