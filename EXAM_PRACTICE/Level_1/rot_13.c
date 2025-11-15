/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_13.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 23:31:20 by nkuydin           #+#    #+#             */
/*   Updated: 2025/11/04 09:38:53 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

// int	main(int argc, char **argv)
// {
//     int        i;
//     char    res;

//     i = 0;
//     if (argc == 2)
//     {
//         while (argv[1][i])
//         {
//             if ((argv[1][i] >= 'a' && argv[1][i] <= 'n')
//             || (argv[1][i] >= 'A' && argv[1][i] <= 'N'))
//             {
//                 argv[1][i] = 'm' - argv[1][i];
//                 argv[1][i] = 'z' - argv[1][i];
//             }
//             else if ((argv[1][i] >= 'm' && argv[1][i] <= 'z')
//             || (argv[1][i] >= 'M' && argv[1][i] <= 'Z'))
//             {
//                 argv[1][i] = argv[1][i] - 'n';
//                 argv[1][i] = 'a' + argv[1][i];
//             }
//             write(1, &argv[1][i], 1);
//             i++;
//         }
//     }
//     write (1, "\n", 1);
//     return (0);
// }

int	main(int argc, char **argv)
{
	int		i;
	char	res;

	i = 0;
	if (argc == 2)
	{
		while (argv[1][i])
		{
			if ((argv[1][i] >= 97 && argv[1][i] <= 109)
			|| (argv[1][i] >= 65 && argv[1][i] <= 77))
			{
				argv[1][i] = 109 - argv[1][i];
				argv[1][i] = 122 - argv[1][i];
			}
			else if ((argv[1][i] >= 110 && argv[1][i] <= 122)
			|| (argv[1][i] >= 78 && argv[1][i] <= 90))
			{
				argv[1][i] = argv[1][i] - 110;
				argv[1][i] = 97 + argv[1][i];
			}
			write(1, &argv[1][i], 1);
			i++;
		}
	}
	write (1, "\n", 1);
	return (0);
}
