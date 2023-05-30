/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:46:36 by aharrass          #+#    #+#             */
/*   Updated: 2023/05/30 00:31:46 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_point(t_mlx *ptr, t_coords coords, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			map_mlx_pixel_put(&ptr->map, coords.x + i, coords.y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_player(t_mlx *ptr, t_coords coords, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			map_mlx_pixel_put(&ptr->map, coords.x - size / 2 + i, coords.y
				- size / 2 + j, color);
			j++;
		}
		i++;
	}
}

void	draw_line(t_mlx *mlx, int i)
{
	double	size;

	size = 0;
	while (size < mlx->rays.distance[i])
	{
		ft_mlx_pixel_put(mlx, mlx->p.x + size * cos(mlx->rays.ray_angle[i]),
			mlx->p.y + size * sin(mlx->rays.ray_angle[i]), 0x0703c6);
		size += 0.1;
	}
}

void	draw_direc(t_mlx *mlx)
{
	double	size;

	size = 0;
	while (size < TILE_SIZE / MAP_SCALE)
	{
		map_mlx_pixel_put(&mlx->map, mlx->p.x / MAP_SCALE + size
			* cos(mlx->p.angle), mlx->p.y / MAP_SCALE + size
			* sin(mlx->p.angle), 0x0703c6);
		size += 0.1;
	}
}
