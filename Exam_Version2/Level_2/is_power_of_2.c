/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_power_of_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 20:39:10 by nkuydin           #+#    #+#             */
/*   Updated: 2025/11/20 21:26:36 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Assignment name  : is_power_of_2
Expected files   : is_power_of_2.c
Allowed functions: None
--------------------------------------------------------------------------------

Write a function that determines if a given number is a power of 2.

This function returns 1 if the given number is a power of 2, otherwise
it returns 0.

Your function must be declared as follows:

int	    is_power_of_2(unsigned int n);
*/

// continuosly divide the number by 2, on the condition that the given
// number is even. After the last possible division, if the value of the
// number is equal to 1, it is a power of 2. Otherwise, it is not.

#include <stdio.h>

int	is_power_of_2(unsigned int n)
{
	while (n % 2 == 0)
		n /= 2;
	if (n == 1)
		return (1);
	return (0);
}

int	main(void)
{
	printf("%d", is_power_of_2(30));
}
