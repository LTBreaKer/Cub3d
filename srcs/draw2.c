/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:42:56 by aharrass          #+#    #+#             */
/*   Updated: 2023/05/30 00:33:49 by aharrass         ###   ########.fr       */
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

int	set_tx_id(t_rays *rays, int ray_id)
{
	(void)rays;
	(void)ray_id;
	if (rays->vertical_hit[ray_id])
	{
		if (rays->facing_left[ray_id])
			return (WE);
		else
			return (EA);
	}
	else
	{
		if (rays->facing_up[ray_id])
			return (NO);
		else
			return (SO);
	}
}

int	get_color(t_mlx *mlx, int x, int y, int tx_id)
{
	char	*dst;

	dst = mlx->tx[tx_id].addr + (y * mlx->tx[tx_id].line_length + x
			* (mlx->tx[tx_id].bpp / 8));
	return (*(unsigned int *)dst);
}

void	draw_wall(t_mlx *mlx, t_coords coords, int ray_id)
{
	t_coords	tmp;
	int			color;
	double		texutre_x;
	double		texture_y;
	double		texture_step;
	int			tx_id;
	double		distance;

	tmp.x = coords.x;
	tx_id = set_tx_id(&mlx->rays, ray_id);
	if (mlx->rays.vertical_hit[ray_id])
		texutre_x = (double)((fmod(mlx->rays.wall_hit_y[ray_id], TILE_SIZE))
				/ TILE_SIZE) *mlx->tx[tx_id].width;
	else
		texutre_x = (double)((fmod(mlx->rays.wall_hit_x[ray_id], TILE_SIZE))
				/ TILE_SIZE) *mlx->tx[tx_id].width;
	texture_step = (double)mlx->tx[tx_id].width / mlx->wall.wall_height;
	while (tmp.x < WIN_WIDTH && tmp.x < coords.x + mlx->wall.rect_width)
	{
		tmp.y = coords.y;
		while (tmp.y < WIN_HEIGHT && tmp.y < coords.y + mlx->wall.wall_height)
		{
			distance = tmp.y + (mlx->wall.wall_height / 2) - (WIN_HEIGHT / 2);
			texture_y = distance * (mlx->tx[tx_id].height
					/ mlx->wall.wall_height);
			color = get_color(mlx, texutre_x, texture_y, tx_id);
			ft_mlx_pixel_put(mlx, tmp.x, tmp.y, color);
			tmp.y++;
		}
		texutre_x += texture_step;
		if (texutre_x > mlx->tx[tx_id].width)
			texutre_x = mlx->tx[tx_id].width;
		tmp.x++;
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
