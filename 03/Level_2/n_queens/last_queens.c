/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_queens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 16:37:17 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/02/08 18:06:59 by Nikita_Kuyd      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void    print_set(int n, int *pos)
{
    int i = 0;
    
    while (i < n)
    {
        if (i > 0)
            fprintf(stdout, " ");
        fprintf(stdout, "%d", pos[i]);
        i++;
    }
    fprintf(stdout, "\n");
}

int abs_int(int x)
{
    if (x < 0)
        x *= -1;
    return (x);
}

int is_safe(int row, int column, int *pos)
{
    int prev_col = 0;
    int prev_row = 0;

    while (prev_col < column)
    {
        prev_row = pos[prev_col];
        if (prev_row == row)
            return (0);
        if (abs_int(prev_col - column) == abs_int(prev_row - row))
            return (0);
        prev_col++;
    }
    return (1);
}

void    solve(int n, int column, int *pos)
{
    int row = 0;

    if (column == n)
    {
        print_set(n, pos);
        return ;
    }
    while (row < n)
    {
        if (is_safe(row, column, pos))
        {
            pos[column] = row;
            solve(n, column + 1, pos);
        }
        row++;
    }
}

int main(int argc, char **argv)
{
    int *pos;
    int n = 0;

    if (argc != 2)
        return (1);
    n = atoi(argv[1]);
    if (n <= 0)
        return (1);
    pos = malloc(sizeof(int) * (n));
    if (!pos)
        return (1);
    solve(n, 0, pos);
    free(pos);
    return (0);
}
