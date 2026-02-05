/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 21:03:11 by nkuydin           #+#    #+#             */
/*   Updated: 2025/11/21 16:27:57 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Assignment name	: ft_strpbrk
Expected files	: ft_strpbrk.c
Allowed functions: None
---------------------------------------------------------------

Reproduce exactly the behavior of the function strpbrk
(man strpbrk).

The function should be prototyped as follows:

char	*ft_strpbrk(const char *s1, const char *s2);
*/

#include <stdio.h>

char	*ft_strpbrk(const char *s1, const char *s2)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	res = (char *)s1;
	while (s1[i])
	{
		j = 0;
		while (s2[j])
		{
			if (s1[i] == s2[j])
				return (res);
			j++;
		}
		res++;
		i++;
	}
	return (NULL);
}

int	main(void)
{
	char	*s1;
	char	*s2;

	s1 = "abc";
	s2 = "cba";
	printf("%s", ft_strpbrk(s1, s2));
}
