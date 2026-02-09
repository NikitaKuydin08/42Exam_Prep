/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tsp_1h.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 11:58:35 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/02/09 12:16:19 by Nikita_Kuyd      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct s_tsp
{
    int n;
    float x[11];
    float y[11];
    float dist[11][11];
    int   visited[11];
    float best_road;
}   t_tsp;

void    read_cities(t_tsp *t)
{
    while (t->n < 11 && (fscanf(stdin, "%f, %f\n", &t->x[t->n], &t->y[t->n])) == 2)
        t->n++;
}

float   calculate_dist(float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    return (sqrtf(dx * dx + dy * dy));
}

void    build_distance(t_tsp *tsp)
{
    int i = 0;
    int j = 0;

    while (i < tsp->n)
    {
        j = 0;
        while (j < tsp->n)
        {
            tsp->dist[i][j] = calculate_dist(tsp->x[i], tsp->y[i], tsp->x[j], tsp->y[j]);
            j++;
        }
        i++;
    }
}

void    solve(t_tsp *tsp, int count, int cur, float cost)
{
    int i = 1;
    float total;

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
    read_cities(tsp);
    if (tsp->n <= 1)
    {
        fprintf(stdout, "0.0\n");
        return (0);
    }
    while (i < tsp->n)
    {
        tsp->visited[i] = 0;
        i++;
    }
    tsp->visited[0] = 1;
    build_distance(tsp);
    tsp->best_road = 1e30f;
    solve(tsp, 1, 0, 0.0f);
    fprintf(stdout, "%.2f\n", tsp->best_road);
    free(tsp);
    return (0);
}
