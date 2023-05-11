/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:46:36 by aharrass          #+#    #+#             */
/*   Updated: 2023/05/11 08:58:39 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
			mlx_pixel_put(ptr->mlx_ptr, ptr->win_ptr, coords.x + i, coords.y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_circle(t_mlx *mlx, t_coords coords, int radius, int color)
{
	double i;

	i = 0;
	while (i < 360)
	{
		mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, coords.x + radius * cos(i), coords.y
				+ radius * sin(i), color);
		i += 0.1;
	}
}

void	draw_line(t_mlx *mlx, t_coords coords, double angle, int color)
{
	double	i;
	double	j;

	i = 0;
	j = 0;
	while (i < 500)
	{
		mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, coords.x + i * cos(angle), coords.y
				+ i * sin(angle), color);
		i += 0.1;
	}
}