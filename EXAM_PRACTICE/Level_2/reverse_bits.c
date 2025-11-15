/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_bits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 12:35:28 by nkuydin           #+#    #+#             */
/*   Updated: 2025/11/07 11:25:15 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/*
Assignment name  : reverse_bits
Expected files   : reverse_bits.c
Allowed functions:
--------------------------------------------------------------------------------

Write a function that takes a byte, reverses it, bit by bit (like the
example) and returns the result.

Your function must be declared as follows:

unsigned char	reverse_bits(unsigned char octet);

Example:

  1 byte
_____________
 0010  0110
     ||
     \/
 0110  0100
*/

// Reverse bits bit by bit means to fip the order of the binary digits(bits)
// in a number, so the least significant bit becomes the most significant bit
// and vice versa

// frees the space at reversed bits at LSB, store LSB from octet, do the right
// shift on octet to get new LSB, repest this shit multiple times, while
// index > 0

unsigned char	reverse_bits(unsigned char octet)
{
	unsigned char	reversed_bits;
	int				i;

	i = 8;
	reversed_bits = 0;
	while (i > 0)
	{
		reversed_bits = (reversed_bits << 1) | (octet & 1);
		octet = octet >> 1;
		i--;
	}
	return (reversed_bits);
}

