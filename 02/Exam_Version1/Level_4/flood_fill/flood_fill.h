/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:15:36 by nkuydin           #+#    #+#             */
/*   Updated: 2025/11/14 17:00:11 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLOOD_FILL_H
# define FLOOD_FILL_H

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

void	flood_fill(char **tab, t_point size, t_point begin);


#endif