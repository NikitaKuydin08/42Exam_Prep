/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_tsp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 18:54:04 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/02/08 19:44:05 by Nikita_Kuyd      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>

typedef struct s_tsp
{
    int n;
    float x[11];
    float y[11];
    float dist[11][11];
    float   best_road;
    int     visited[11];
}   t_tsp;

void    read_map(t_tsp *tsp)
{
    while (tsp->n < 11 && (fscanf(stdin, "%f, %f\n", &tsp->x[tsp->n], &tsp->y[tsp->n])) == 2)
        tsp->n++;
}

float calculate_dist(float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    return (sqrtf(dx * dx + dy * dy));
}

void    build_dist(t_tsp *t)
{
    int i = 0;
    int j = 0;

    while (i < t->n)
    {
        j = 0;
        while (j < t->n)
        {
            t->dist[i][j] = calculate_dist(t->x[i], t->y[i], t->x[j], t->y[j]);
            j++;
        }
        i++;
    }
}

void    solve(t_tsp *tsp, int count, int cur, float cost)
{
    int i = 1;
    float   total;
    
    if (cost >= tsp->best_road)
        return ;
    if (count == tsp->n)
    {
        total = cost + tsp->dist[cur][0];
        if (total < tsp->best_road)
            tsp->best_road = total;
        return ;
    }
    while (i < tsp->n)
    {
        if (!tsp->visited[i])
        {
            tsp->visited[i] = 1;
            solve(tsp, count + 1, i, cost + tsp->dist[cur][i]);
            tsp->visited[i] = 0;
        }
        i++;
    }
}

int main(void)
{
    t_tsp *tsp;
    int     i = 0;

    tsp = malloc(sizeof(t_tsp));
    if (!tsp)
        return (1);
    tsp->n = 0;
    read_map(tsp);
    if (tsp->n <= 0)
    {
        free(tsp);
        fprintf(stdout, "0.00\n");
        return (1);
    }
    while (i < tsp->n)
    {
        tsp->visited[i] = 0;
        i++;
    }
    tsp->best_road = 1e30f;
    tsp->visited[0] = 1;
    build_dist(tsp);
    solve(tsp, 1, 0, 0.0f);
    fprintf(stdout, "%.2f\n", tsp->best_road);
    free(tsp);
    return (0);
}
