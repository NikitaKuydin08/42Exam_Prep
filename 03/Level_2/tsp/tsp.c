/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tsp1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 18:33:44 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/02/08 00:50:11 by Nikita_Kuyd      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct s_city
{
    int     n;
    float x[11];
    float y[11];
    float dist[11][11];
    int   visited[11];
    float best_road;
}   t_city;

void    read_city_stdin(t_city *c)
{
    c->n = 0;

    while (c->n < 11 && (fscanf(stdin, "%f, %f\n", &c->x[c->n], &c->y[c->n])) == 2)
        c->n++;
}

float   calculate_distance(float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    return (sqrtf(dx * dx + dy * dy));
}

void    build_distance(t_city *c)
{
    int i = 0;
    int j;

    while (i < c->n)
    {
        j = 0;
        while (j < c->n)
        {
            c->dist[i][j] = calculate_distance(c->x[i], c->y[i], c->x[j], c->y[j]);
            j++;
        }
        i++;
    }
}

void    solve(t_city *c, int current, int visit_count, float cost)
{
    float   total;
    int     i = 1;

    if (cost >= c->best_road)
        return ;
    if (visit_count == c->n)
    {
        total = cost + c->dist[current][0];
        if (total < c->best_road)
            c->best_road = total;
        return ;
    }
    while (i < c->n)
    {
        if (!c->visited[i])
        {
            c->visited[i] = 1;
            cost += c->dist[current][i];
            solve(c, i, visit_count + 1, cost);
            cost -= c->dist[current][i];
            c->visited[i] = 0;
        }
        i++;
    }
}

int main(void)
{
    t_city *cities;
    int     i = 0;
    
    cities = malloc(sizeof(t_city));
    if (!cities)
        return (1);
    read_city_stdin(cities);
    if (cities->n <= 1)
    {
        free(cities);
        fprintf(stdout, "0.00\n");
        return (0);
    }
    build_distance(cities);
    while (i < cities->n)
    {
        cities->visited[i] = 0;
        i++;
    }
    cities->best_road = 1e30f;
    cities->visited[0] = 1;
    solve(cities, 0, 1, 0.0f);
    fprintf(stdout, "%.2f\n", cities->best_road);
    free(cities);
    return (0);
}
