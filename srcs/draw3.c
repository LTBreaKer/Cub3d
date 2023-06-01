/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 21:01:29 by aharrass          #+#    #+#             */
/*   Updated: 2023/06/01 11:31:40 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	map_mlx_pixel_put(t_map *map, int x, int y, int color)
{
	char	*dst;

	dst = map->addr + (y * map->line_length + x * (map->bpp / 8));
	*(unsigned int *)dst = color;
}

void	mini_mlx_pixel_put(t_mini_map *mini_map, int x, int y, int color)
{
	char	*dst;

	dst = mini_map->addr + (y * mini_map->line_length + x * (mini_map->bpp
				/ 8));
	*(unsigned int *)dst = color;
}

void	wall_slide(t_mlx *mlx)
{
	double	new_x;
	double	new_y;

	new_x = mlx->p.x;
	new_y = mlx->p.y;
	if (mlx->rays.vertical_hit[(RAYS - 1) / 2])
	{
		if (mlx->rays.facing_down[(RAYS - 1) / 2])
			new_y += mlx->p.move_speed;
		else
			new_y -= mlx->p.move_speed;
		check_update(mlx, new_x, new_y);
	}
	else
	{
		if (mlx->rays.facing_right[(RAYS - 1) / 2])
			new_x += mlx->p.move_speed;
		else
			new_x -= mlx->p.move_speed;
		check_update(mlx, new_x, new_y);
	}
}

int	get_color(t_mlx *mlx, int x, int y, int tx_id)
{
	char	*dst;

	dst = mlx->tx[tx_id].addr + (y * mlx->tx[tx_id].line_length + x
			* (mlx->tx[tx_id].bpp / 8));
	return (*(unsigned int *)dst);
}
