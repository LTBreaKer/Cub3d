/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:42:56 by aharrass          #+#    #+#             */
/*   Updated: 2023/05/20 00:31:48 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_ceiling(t_mlx *mlx, t_coords coords)
{
	t_coords	tmp;

	tmp.y = 0;
	while (tmp.y < coords.y)
	{
		tmp.x = coords.x;
		while (tmp.x < coords.x + mlx->wall.rect_width)
		{
			ft_mlx_pixel_put(mlx, tmp.x, tmp.y, mlx->map.ceiling_color);
			tmp.x++;
		}
		tmp.y++;
	}
}

void	draw_wall(t_mlx *mlx, t_coords coords)
{
	t_coords	tmp;
	
	tmp.y = coords.y;
	while (tmp.y < WIN_HEIGHT && tmp.y < coords.y + mlx->wall.wall_height)
	{
		tmp.x = coords.x;
		while (tmp.x < WIN_WIDTH && tmp.x < coords.x + mlx->wall.rect_width)
		{
			ft_mlx_pixel_put(mlx, tmp.x, tmp.y, 0x2F2504);
			tmp.x++;
		}
		tmp.y++;
	}
}

void	draw_floor(t_mlx *mlx, t_coords coords)
{
	t_coords	tmp;

	tmp.y = coords.y + mlx->wall.wall_height;
	while (tmp.y < WIN_HEIGHT)
	{
		tmp.x = coords.x;
		while (tmp.x < coords.x + mlx->wall.rect_width)
		{
			ft_mlx_pixel_put(mlx, tmp.x, tmp.y, mlx->map.floor_color);
			tmp.x++;
		}
		tmp.y++;
	}
}