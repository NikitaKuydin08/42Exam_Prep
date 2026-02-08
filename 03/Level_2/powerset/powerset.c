/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 21:27:44 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/02/08 00:48:31 by Nikita_Kuyd      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_set
{
    int *arr;
    int *subset;
    int target;
    int size_arr;
}   t_set;

void    print_subset(int *set, int len)
{
    int i = 0;

    while (i < len)
    {
        if (i > 0)
            printf(" ");
        printf("%d", set[i]);
        i++;
    }
    printf("\n");
}

void    backtracking(t_set *set, int i, int current_sum, int i_subset)
{
    if (i == set->size_arr)
    {
        if (current_sum == set->target)
            print_subset(set->subset, i_subset);
        return ;
    }
    set->subset[i_subset] = set->arr[i];
    current_sum += set->arr[i];
    i_subset++;
    backtracking(set, i + 1, current_sum, i_subset);
    current_sum -= set->arr[i];
    i_subset--;
    backtracking(set, i + 1, current_sum, i_subset);
}

int main(int argc, char **argv)
{
    int i = 0;
    int current_sum = 0;
    int size_subset = 0;
    t_set *struc;
    
    if (argc < 3)
        exit(1);
    struc = malloc(sizeof(t_set));
    if (!struc)
        exit(1);
    struc->target = atoi(argv[1]);
    struc->size_arr = argc - 2;
    struc->arr = malloc(sizeof(int) * struc->size_arr);
    if (!struc->arr)
        exit(1);
    struc->subset = malloc(sizeof(int) * struc->size_arr);
    if (!struc->subset)
        exit(1);
    while (i < struc->size_arr)
    {
        struc->arr[i] = atoi(argv[2 + i]);
        i++;
    }
    backtracking(struc, 0, current_sum, size_subset);
    free(struc->arr);
    free(struc->subset);
    free(struc);
    return (0);
}
