/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_rays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 00:54:46 by aharrass          #+#    #+#             */
/*   Updated: 2023/06/01 11:13:31 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_horiz(t_mlx *mlx, int i, double hor_dist, t_coords *hor_inter)
{
	mlx->rays.vertical_hit[i] = 0;
	mlx->rays.distance[i] = hor_dist;
	mlx->rays.wall_hit_x[i] = hor_inter[i].x;
	mlx->rays.wall_hit_y[i] = hor_inter[i].y;
}

void	set_vert(t_mlx *mlx, int i, double ver_dist, t_coords *ver_inter)
{
	mlx->rays.vertical_hit[i] = 1;
	mlx->rays.distance[i] = ver_dist;
	mlx->rays.wall_hit_x[i] = ver_inter[i].x;
	mlx->rays.wall_hit_y[i] = ver_inter[i].y;
}

void	cast_rays(t_mlx *mlx)
{
	int			i;
	t_coords	hor_inter[RAYS];
	t_coords	ver_inter[RAYS];
	double		hor_dist;
	double		ver_dist;

	(void)ver_inter;
	hor_dist = DBL_MAX;
	ver_dist = DBL_MAX;
	i = 0;
	while (i < RAYS)
	{
		if (horizontal_inter(mlx, &hor_inter[i], i) == 0)
			hor_dist = sqrt(pow(hor_inter[i].x - mlx->p.x, 2)
					+ pow(hor_inter[i].y - mlx->p.y, 2));
		if (vertical_inter(mlx, &ver_inter[i], i) == 0)
			ver_dist = sqrt(pow(ver_inter[i].x - mlx->p.x, 2)
					+ pow(ver_inter[i].y - mlx->p.y, 2));
		if (hor_dist <= ver_dist)
			set_horiz(mlx, i, hor_dist, hor_inter);
		else
			set_vert(mlx, i, ver_dist, ver_inter);
		i++;
	}
}

void	rays(t_mlx *mlx)
{
	double	ray_angle;
	int		i;

	i = 0;
	ray_angle = mlx->p.angle - FOV / 2;
	while (i < RAYS)
	{
		mlx->rays.ray_angle[i] = ray_angle;
		if (mlx->rays.ray_angle[i] < 0)
			mlx->rays.ray_angle[i] += 2 * M_PI;
		if (mlx->rays.ray_angle[i] > 2 * M_PI)
			mlx->rays.ray_angle[i] -= 2 * M_PI;
		ray_angle += (FOV / RAYS);
		i++;
	}
}
