/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_powerset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 15:33:39 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/02/08 15:48:28 by Nikita_Kuyd      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct s_set
{
    int target;
    int *subset;
    int *arr;
    int size_arr;
}   t_set;

void    print_solutions(int *s, int len)
{
    int i = 0;

    while (i < len)
    {
        if (i > 0)
            printf(" ");
        printf("%d", s[i]);
        i++;
    }
    printf("\n");
}

void    solve(t_set *s, int i, int cur_sum, int size_subset)
{
    if (i == s->size_arr)
    {
        if (cur_sum == s->target)
            print_solutions(s->subset, size_subset);
        return ;
    }
    s->subset[size_subset] = s->arr[i];
    cur_sum += s->arr[i];
    size_subset++;
    solve(s, i + 1, cur_sum, size_subset);
    cur_sum -= s->arr[i];
    size_subset--;
    solve(s, i + 1, cur_sum, size_subset);
}

int main(int argc, char **argv)
{
    t_set *s;
    int i = 0;
    int size_subset = 0;

    if (argc < 3)
        return (1);
    s = malloc(sizeof(t_set));
    if (!s)
        return (1);
    s->target = atoi(argv[1]);
    s->size_arr = argc - 2;
    s->arr = malloc(sizeof(int) * (s->size_arr));
    if (!s->arr)
        return (1);
    while (i < s->size_arr)
    {
        s->arr[i] = atoi(argv[i + 2]);
        i++;
    }
    s->subset = malloc(sizeof(int) * (s->size_arr));
    if (!s->subset)
        return (1);
    solve(s, 0, 0, size_subset);
    free(s->arr);
    free(s->subset);
    free(s);
    return (0);
}
