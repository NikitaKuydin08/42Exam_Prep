/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queen.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 20:32:22 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/02/04 15:17:26 by Nikita_Kuyd      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Allowed functions : atoi, fprintf, write, calloc, malloc, free, realloc, stdout, stderr

#include "queen.h"

int abs_int(int x)
{
    if (x < 0)
        x *= -1;
    return (x);
}

void print_solutions(int *pos, int n)
{
    int i = 0;
    
    while (i < n)
    {
        fprintf(stdout, "%d", pos[i]);
        if (i != n - 1)
            fprintf(stdout, " ");
        i++;
    }
    fprintf(stdout, "\n");
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
        if ((abs_int(prev_row - row) == abs_int(prev_col - column)))
            return (0);
        prev_col++;
    }
    return (1);
}

void    backtracking(int column, int n, int *pos)
{
    int row = 0;
    
    if (column == n)
    {
        print_solutions(pos, n);
        return ;
    }
    while (row < n)
    {
        if (is_safe(row, column, pos))
        {
            pos[column] = row;
            backtracking(column + 1, n, pos);
        }
        row++;
    }
}

int main(int argc, char **argv)
{
    int n;
    int *pos;

    if (argc != 2)
        return (0);
    n = atoi(argv[1]);
    if (n <= 0)
        return (0);
    pos = malloc(sizeof(int) * n);
    if (!pos)
        return (0);
    backtracking(0, n, pos);
    free(pos);
    return (0);
}
