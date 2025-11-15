/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rrange.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 10:36:20 by nkuydin           #+#    #+#             */
/*   Updated: 2025/11/08 10:51:15 by nkuydin          ###   ########.fr       */
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

#include <stdlib.h>
#include <stdio.h>

int	*ft_rrange(int start, int end)
{
	int	len;
	int	*tab;
	int	i;

	i = 0;
	if (end >= start)
		len = end - start + 1;
	else
		len = start - end + 1;
	tab = malloc(sizeof(int) * len);
	if (!tab)
		return (NULL);
	if (end >= start)
	{
		while (i < len)
		{
			tab[i] = end;
			i++;
			end--;
		}
	}
	else
	{
		while (i < len)
		{
			tab[i] = end;
			i++;
			end++;
		}
	}
	return (tab);
}

int	main(void)
{
	int	*tab;
	int	i;
	int	len;

	i = 0;
	len = 4;
	tab = ft_rrange(0, -3);
	while (i < len)
	{
		printf("%d ", tab[i]);
		i++;
	}
	free(tab);
}
