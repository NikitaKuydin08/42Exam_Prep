/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:13:24 by nkuydin           #+#    #+#             */
/*   Updated: 2025/11/06 19:14:36 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Assignment name  : max
Expected files   : max.c
Allowed functions:
--------------------------------------------------------------------------------

Write the following function:

int		max(int* tab, unsigned int len);

The first parameter is an array of int, the second is the number of elements in
the array.

The function returns the largest number found in the array.

If the array is empty, the function returns 0.
*/

#include <stdio.h>

int	max(int *tab, unsigned int len)
{
	int	i;
	int	largest;

	i = 1;
	if (!tab || len == 0)
		return (0);
	largest = tab[0];
	while (i < len)
	{
		if (tab[i] > largest)
			largest = tab[i];
		i++;
	}
	return (largest);
}

// int	main(void)
// {
// 	int	tab[] = {1, 2, 7, 4, 67, 43, 23};

// 	printf("%i", max(tab, 7));
// }
