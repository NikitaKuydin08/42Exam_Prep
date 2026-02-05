/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 11:57:51 by nkuydin           #+#    #+#             */
/*   Updated: 2025/11/07 09:59:53 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/*
Assignment name  : print_bits
Expected files   : print_bits.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a function that takes a byte, and prints it in binary WITHOUT A NEWLINE
AT THE END.

Your function must be declared as follows:

void	print_bits(unsigned char octet);

Example, if you pass 2 to print_bits, it will print "00000010"
*/

// A char in C is guaranteed to be 1 byte, so i = 8

void	print_bits(unsigned char octet)
{
	int				i;
	unsigned char	bits;

	i = 8;
	bits = 0;
	while (i-- > 0)
	{
		bits = ((octet >> i) & 1) + '0';
		write(1, &bits, 1);
	}
}

// int	main(void)
// {
// 	print_bits(-1);
// }

// Shift the bit of octet to the right i times and use the bitwise AND
// operator with 1 to get the bit value. Then add 48 ('0') to convert
// the bit value to its ASCII representation ('0' or '1')