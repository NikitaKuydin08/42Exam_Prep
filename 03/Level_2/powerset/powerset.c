/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:10:46 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/01/28 17:14:15 by Nikita_Kuyd      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "powerset.h"

// Allowed functions: atoi, printf, fprintf, malloc, calloc, realloc, free, stdout, write

void    print_subset(int *subset, int len)
{
    int i = 0;

    while (i < len)
    {
        if (i > 0)
            printf(" ");
        printf("%d", subset[i]);
        i++;
    }
    printf("\n");
}

void    backtrack(t_set *struc, int i, int current_sum, int size_subset)
{
    if (i == struc->size_arr)
    {
        if (current_sum == struc->target)
            print_subset(struc->subset, size_subset);
        return ;
    }
    struc->subset[size_subset] = struc->arr[i];
    current_sum = current_sum + struc->arr[i];
    size_subset++;
    backtrack(struc, i + 1, current_sum, size_subset);
    current_sum = current_sum - struc->arr[i];
    size_subset--;
    backtrack(struc, i + 1, current_sum, size_subset);
}

int main(int argc, char **argv)
{
    t_set   *struc;
    
    int size_subset = 0;
    int i = 0;
    int index = 0;
    int current_sum = 0;

    if (argc < 3)
        return (1);
    struc = malloc(sizeof (t_set));
    struc->target = atoi(argv[1]);
    struc->size_arr = argc - 2;
    struc->arr = malloc(sizeof(int) * (struc->size_arr));
    if (!struc->arr)
        exit(1);
    while (i < struc->size_arr)
    {
        struc->arr[i] = atoi(argv[i + 2]);
        i++;
    }
    struc->subset = malloc(sizeof(int) * struc->size_arr);
    if (!struc->subset)
        exit(1);
    backtrack(struc, index, current_sum, size_subset);
    free(struc->arr);
    free(struc->subset);
    return (0);
}
