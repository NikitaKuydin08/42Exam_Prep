/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queens1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 23:46:16 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/02/07 12:49:54 by Nikita_Kuyd      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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
        if (i > 0)
            fprintf(stdout, " ");
        fprintf(stdout, "%d", pos[i]);
        i++;
    }
    fprintf(stdout, "\n");
}

int is_safe(int col, int row, int *pos)
{
    int prev_col = 0;
    int prev_row = 0;

    while (prev_col < col)
    {
        prev_row = pos[prev_col];
        if (prev_row == row)
            return (0);
        if (abs_int(prev_row - row) == abs_int(prev_col - col))
            return (0);
        prev_col++;
    }
    return (1);
}

void solve(int column, int n, int *pos)
{
    int row = 0;
    
    if (column == n)
    {
        print_solutions(pos, n);
        return ;
    }
    while (row < n)
    {
        if (is_safe(column, row, pos))
        {
            pos[column] = row;
            solve(column + 1, n, pos);
        }
        row++;
    }
}

int main(int argc, char **argv)
{
    int n;
    int *pos;
    int column = 0;
    
    if (argc != 2)
        return (1);
    n = atoi(argv[1]);
    if (n <= 0)
        return (1);
    pos = malloc(sizeof(int) * n);
    if (!pos)
        return (1);
    solve(column, n, pos);
    free(pos);
    return (0);
}
