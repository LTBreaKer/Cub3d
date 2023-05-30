/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 00:51:19 by aharrass          #+#    #+#             */
/*   Updated: 2023/05/30 01:00:56 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	horizontal_inter(t_mlx *mlx, t_coords *hor_inter, int i)
{
	double	xstep;
	double	ystep;

	if (mlx->rays.ray_angle[i] == 0 || mlx->rays.ray_angle[i] == M_PI
		|| mlx->rays.ray_angle[i] == 2 * M_PI)
		return (hor_inter->x = 0, hor_inter->y = 0, 1);
	ray_direction(&mlx->rays, i);
	hor_inter->y = floor(mlx->p.y / TILE_SIZE) * TILE_SIZE;
	if (mlx->rays.facing_down[i])
		hor_inter->y += TILE_SIZE;
	hor_inter->x = mlx->p.x + (hor_inter->y - mlx->p.y)
		/ tan(mlx->rays.ray_angle[i]);
	if (hor_inter->x < 0 || floor(hor_inter->x
			/ TILE_SIZE) >= ft_strlen(mlx->map.map[(int)floor(hor_inter->y
					/ TILE_SIZE)]))
		return (hor_inter->x = 0, hor_inter->y = 0, 1);
	if (hor_inter->y < 0 || floor(hor_inter->y
			/ TILE_SIZE) >= ft_double_strlen(mlx->map.map))
		return (hor_inter->x = 0, hor_inter->y = 0, 1);
	ystep = TILE_SIZE;
	xstep = TILE_SIZE / tan(mlx->rays.ray_angle[i]);
	corr_steps(mlx->rays, &xstep, &ystep, i);
	while (hor_inter->x >= 0 && hor_inter->y >= 0 && floor(hor_inter->y
			/ TILE_SIZE) < ft_double_strlen(mlx->map.map) && floor(hor_inter->x
			/ TILE_SIZE) < ft_strlen(mlx->map.map[(int)floor(hor_inter->y
					/ TILE_SIZE)]))
	{
		if (mlx->rays.facing_up[i])
			hor_inter->y--;
		if (wall_check(hor_inter->x, hor_inter->y, mlx->map.map) == 0)
		{
			if (mlx->rays.facing_up[i])
				hor_inter->y++;
			break ;
		}
		else
		{
			hor_inter->x += xstep;
			hor_inter->y += ystep;
		}
	}
	return (0);
}

int	vertical_inter(t_mlx *mlx, t_coords *ver_inter, int i)
{
	double	xstep;
	double	ystep;

	if (mlx->rays.ray_angle[i] == M_PI / 2 || mlx->rays.ray_angle[i] == 3 * M_PI
		/ 2)
		return (ver_inter->x = 0, ver_inter->y = 0, 1);
	ray_direction(&mlx->rays, i);
	ver_inter->x = floor(mlx->p.x / TILE_SIZE) * TILE_SIZE;
	if (mlx->rays.facing_right[i])
		ver_inter->x += TILE_SIZE;
	ver_inter->y = mlx->p.y + (ver_inter->x - mlx->p.x)
		* tan(mlx->rays.ray_angle[i]);
	if (ver_inter->y < 0 || floor(ver_inter->y
			/ TILE_SIZE) >= ft_double_strlen(mlx->map.map))
		return (ver_inter->x = 0, ver_inter->y = 0, 1);
	if (ver_inter->x < 0 || floor(ver_inter->x
			/ TILE_SIZE) >= ft_strlen(mlx->map.map[(int)floor(ver_inter->y
					/ TILE_SIZE)]))
		return (ver_inter->x = 0, ver_inter->y = 0, 1);
	xstep = TILE_SIZE;
	ystep = TILE_SIZE * tan(mlx->rays.ray_angle[i]);
	corr_steps(mlx->rays, &xstep, &ystep, i);
	while (ver_inter->x >= 0 && ver_inter->y >= 0 && floor(ver_inter->y
			/ TILE_SIZE) < ft_double_strlen(mlx->map.map) && floor(ver_inter->x
			/ TILE_SIZE) < ft_strlen(mlx->map.map[(int)floor(ver_inter->y
					/ TILE_SIZE)]))
	{
		if (mlx->rays.facing_left[i])
			ver_inter->x--;
		if (wall_check(ver_inter->x, ver_inter->y, mlx->map.map) == 0)
		{
			if (mlx->rays.facing_left[i])
				ver_inter->x++;
			break ;
		}
		else
		{
			ver_inter->x += xstep;
			ver_inter->y += ystep;
		}
	}
	return (0);
}
