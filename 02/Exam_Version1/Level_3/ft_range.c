/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 10:08:39 by nkuydin           #+#    #+#             */
/*   Updated: 2025/11/08 10:35:59 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Assignment name  : ft_range
Expected files   : ft_range.c
Allowed functions: malloc
--------------------------------------------------------------------------------

Write the following function:

int     *ft_range(int start, int end);

It must allocate (with malloc()) an array of integers, fill it with consecutive
values that begin at start and end at end (Including start and end !), then
return a pointer to the first value of the array.

Examples:

- With (1, 3) you will return an array containing 1, 2 and 3.
- With (-1, 2) you will return an array containing -1, 0, 1 and 2.
- With (0, 0) you will return an array containing 0.
- With (0, -3) you will return an array containing 0, -1, -2 and -3.
*/

#include <stdlib.h>
#include <stdio.h>

int	*ft_range(int start, int end)
{
	int	len;
	int	*tab;
	int	i;

	i = 0;
	if (start <= end)
		len = end - start + 1;
	else
		len = start - end + 1;
	tab = malloc(sizeof(int) * (len));
	if (!tab)
		return (NULL);
	if (start <= end)
	{
		while (i < len)
		{
			tab[i] = start;
			start++;
			i++;
		}
	}
	else
	{
		while (i < len)
		{
			tab[i] = start;
			i++;
			start--;
		}
	}
	return (tab);
}

int	main(void)
{
	int	*tab;
	int	length;
	int	i;

	i = 0;
	length = 4;
	tab = ft_range(0, -3);
	while (i < length)
	{
		printf("%d ", tab[i]);
		i++;
	}
	free(tab);
}
