/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:17:53 by nkuydin           #+#    #+#             */
/*   Updated: 2025/11/06 14:57:06 by nkuydin          ###   ########.fr       */
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

#include <unistd.h>
#include <stdio.h>

char	*ft_strpbrk(const char *s1, const char *s2)
{
	int		i;
	int		j;
	char	*res;

	res = (char *)s1;
	i = 0;
	while (s1[i])
	{
		j = 0;
		while (s2[j])
		{
			if (s1[i] == s2[j])
				return (res);
			j++;
		}
		i++;
		res++;
	}
	return (NULL);
}

// int	main(int argc, char **argv)
// {
// 	(void)argc;
// 	printf("%s\n", ft_strpbrk(argv[1], argv[2]));
// }
