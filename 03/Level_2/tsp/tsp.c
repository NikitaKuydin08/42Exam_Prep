/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tsp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 15:25:01 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/02/04 15:25:11 by Nikita_Kuyd      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tsp.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static float
dist(float x1, float y1, float x2, float y2)
{
	float dx = x1 - x2;
	float dy = y1 - y2;

	return (sqrtf(dx * dx + dy * dy));
}

static int
read_cities(float *x, float *y)
{
	int		n = 0;
	float	cx;
	float	cy;

	while (n < MAX_CITIES && fscanf(stdin, " %f , %f", &cx, &cy) == 2)
	{
		x[n] = cx;
		y[n] = cy;
		n++;
	}
	return (n);
}

static void
build_dist(float d[MAX_CITIES][MAX_CITIES], float *x, float *y, int n)
{
	int i;
	int j;

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			d[i][j] = dist(x[i], y[i], x[j], y[j]);
}

static float
solve_tsp(float d[MAX_CITIES][MAX_CITIES], int n)
{
	int		all = (1 << n) - 1;
	float	*dp = (float *)malloc(sizeof(float) * (all + 1) * n);
	int		mask;
	int		i;
	int		next;
	float	best;

	if (!dp)
		return (-1.0f);
	for (mask = 0; mask <= all; mask++)
		for (i = 0; i < n; i++)
			dp[mask * n + i] = 1e30f;
	dp[1 * n + 0] = 0.0f;
	for (mask = 1; mask <= all; mask++)
	{
		for (i = 0; i < n; i++)
		{
			float cur = dp[mask * n + i];

			if (cur >= 1e29f)
				continue ;
			for (next = 0; next < n; next++)
			{
				int bit = 1 << next;

				if (mask & bit)
					continue ;
				if (cur + d[i][next] < dp[(mask | bit) * n + next])
					dp[(mask | bit) * n + next] = cur + d[i][next];
			}
		}
	}
	best = 1e30f;
	for (i = 0; i < n; i++)
	{
		float cand = dp[all * n + i] + d[i][0];

		if (cand < best)
			best = cand;
	}
	free(dp);
	return (best);
}

int	main(void)
{
	float	x[MAX_CITIES];
	float	y[MAX_CITIES];
	float	d[MAX_CITIES][MAX_CITIES];
	int		n;
	float	best;

	n = read_cities(x, y);
	if (n == 0)
	{
		fprintf(stdout, "0.00\n");
		return (0);
	}
	build_dist(d, x, y, n);
	best = solve_tsp(d, n);
	if (best < 0.0f)
		return (1);
	fprintf(stdout, "%.2f\n", best);
	return (0);
}
