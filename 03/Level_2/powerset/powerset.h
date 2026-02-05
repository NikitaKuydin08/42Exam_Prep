/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:14:45 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/01/26 14:31:37 by Nikita_Kuyd      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POWERSET_H
# define POWERSET_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_set {
    int *arr;
    int size_arr;
    int *subset;
    int target;
}   t_set;

#endif