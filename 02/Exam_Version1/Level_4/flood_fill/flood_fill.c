/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:16:57 by nkuydin           #+#    #+#             */
/*   Updated: 2025/11/14 17:20:30 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flood_fill.h"

void	dfs_algo(char **grid, t_point size, t_point init, char old_char)
{
	if (init.x < 0 || init.x >= size.x || init.y < 0 || init.y >= size.y)
		return ;
	if (grid[init.y][init.x] != old_char)
		return ;
	grid[init.y][init.x] = 'F';
	dfs_algo(grid, size, (t_point){init.x + 1, init.y}, old_char);
	dfs_algo(grid, size, (t_point){init.x - 1, init.y}, old_char);
	dfs_algo(grid, size, (t_point){init.x, init.y + 1}, old_char);
	dfs_algo(grid, size, (t_point){init.x, init.y - 1}, old_char);
}

void	flood_fill(char **tab, t_point size, t_point begin)
{
	char	old_char;
	char	new_char;

	new_char = 'F';
	old_char = tab[begin.y][begin.x];
	if (old_char != new_char)
		dfs_algo(tab, size, begin, old_char);
}
