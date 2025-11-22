/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rrange.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 00:26:56 by nkuydin           #+#    #+#             */
/*   Updated: 2025/11/22 00:49:28 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Assignment name  : ft_rrange
Expected files   : ft_rrange.c
Allowed functions: malloc
--------------------------------------------------------------------------------

Write the following function:

int     *ft_rrange(int start, int end);

It must allocate (with malloc()) an array of integers, fill it with consecutive
values that begin at end and end at start (Including start and end !), then
return a pointer to the first value of the array.

Examples:

- With (1, 3) you will return an array containing 3, 2 and 1
- With (-1, 2) you will return an array containing 2, 1, 0 and -1.
- With (0, 0) you will return an array containing 0.
- With (0, -3) you will return an array containing -3, -2, -1 and 0.
*/

#include <stdio.h>
#include <stdlib.h>

int	*ft_rrange(int start, int end)
{
	int	len;
	int	i;
	int	*res;

	i = 0;
	len = 0;
	if (end > start)
		len = end - start + 1;
	else if (end < start)
		len = (end - start) * (-1) + 1;
	else if (end == start)
		len = 1;
	res = malloc(sizeof(int) * len);
	if (!res)
		return (0);
	if (end >= start)
	{
		while (end >= start)
		{
			res[i] = end;
			i++;
			end--;
		}
	}
	else
	{
		while (end <= start)
		{
			res[i] = end;
			i++;
			end++;
		}
	}
	return (res);
}

int	main(void)
{
	int	*out;
	int	i;
	int	x;

	x = 0;
	out = ft_rrange(0, -3);
	i = 4;
	while (x < i)
	{
		printf("%i ", out[x]);
		x++;
	}
}
