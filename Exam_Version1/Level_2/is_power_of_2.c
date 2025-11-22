/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_power_of_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:07:12 by nkuydin           #+#    #+#             */
/*   Updated: 2025/11/06 17:51:42 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Assignment name  : is_power_of_2
Expected files   : is_power_of_2.c
Allowed functions: None
--------------------------------------------------------------------------------

Write a function that determines if a given number is a power of 2.

This function returns 1 if the given number is a power of 2, otherwise it
returns 0.

Your function must be declared as follows:

int	    is_power_of_2(unsigned int n);
*/

#include <stdio.h>

int	is_power_of_2(unsigned int n)
{
	int	test;

	test = 1;
	while (test <= n)
	{
		if (test == n)
			return (1);
		test = test * 2;
	}
	return (0);
}

// int	main(int argc, char **argv)
// {
// 	unsigned int	i;

// 	i = 10;
// 	(void)argc;
// 	printf("%u", is_power_of_2(i));
// }

// the number that is the power of two is the number that can be divided by 2
// repeatedly untill it reaches 1.