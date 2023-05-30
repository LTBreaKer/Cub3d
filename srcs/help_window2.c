/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_window2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 01:09:25 by aharrass          #+#    #+#             */
/*   Updated: 2023/05/30 01:10:20 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	mouse_hook(int x, int y, t_mlx *mlx)
{
	(void)mlx;
	(void)y; // -100, 2779
	mlx_mouse_hide();
	mlx->keys.mouse_x = x;
	if (mlx->keys.mouse_x > mlx->keys.old_mouse_x)
		mlx->p.angle += mlx->p.rot_speed;
	else if (mlx->keys.mouse_x < mlx->keys.old_mouse_x)
		mlx->p.angle -= mlx->p.rot_speed;
	if (mlx->p.angle > 2 * M_PI)
		mlx->p.angle -= 2 * M_PI;
	else if (mlx->p.angle < 0)
		mlx->p.angle += 2 * M_PI;
	if (mlx->keys.mouse_x == -100 || mlx->keys.mouse_x == 2779)
		mlx->keys.mouse_x = mlx->keys.old_mouse_x;
	mlx->keys.old_mouse_x = mlx->keys.mouse_x;
	return (0);
}

void	crop_map(t_mlx *mlx)
{
	int	x;
	int	y;
	int	x_start;
	int	y_start;
	int	x_end;
	int	y_end;
	int	x_tmp;
	int	color;

	x = 0;
	y = 0;
	x_start = (mlx->p.x / MAP_SCALE) - 100;
	y_start = (mlx->p.y / MAP_SCALE) - 100;
	x_end = (mlx->p.x / MAP_SCALE) + 100;
	y_end = (mlx->p.y / MAP_SCALE) + 100;
	if (x_end > mlx->map.map_width * (TILE_SIZE) / MAP_SCALE)
	{
		x_start -= (x_end - (mlx->map.map_width * (TILE_SIZE) / MAP_SCALE));
		x_end = mlx->map.map_width * (TILE_SIZE) / MAP_SCALE;
	}
	if (y_end > mlx->map.map_height * (TILE_SIZE) / MAP_SCALE)
	{
		y_start -= y_end - (mlx->map.map_height * (TILE_SIZE) / MAP_SCALE);
		y_end = mlx->map.map_height * (TILE_SIZE) / MAP_SCALE;
	}
	if (x_start < 0)
	{
		x_end -= x_start;
		x_start = 0;
	}
	if (y_start < 0)
	{
		y_end -= y_start;
		y_start = 0;
	}
	if (x_end > mlx->map.map_width * (TILE_SIZE) / MAP_SCALE)
		x_end = mlx->map.map_width * (TILE_SIZE) / MAP_SCALE;
	if (y_end > mlx->map.map_height * (TILE_SIZE) / MAP_SCALE)
		y_end = mlx->map.map_height * (TILE_SIZE) / MAP_SCALE;
	while (y_start < y_end && y < 200)
	{
		x_tmp = x_start;
		x = 0;
		while (x_tmp < x_end && x < 200)
		{
			color = get_map_color(&mlx->map, x_tmp, y_start);
			mini_mlx_pixel_put(&mlx->mini_map, x, y, color);
			x_tmp++;
			x++;
		}
		while (x_tmp < 200)
		{
			mini_mlx_pixel_put(&mlx->mini_map, x, y, 0xffffffff);
			x_tmp++;
			x++;
		}
		y_start++;
		y++;
	}
	while (y_start < 200)
	{
		x_tmp = x_start;
		x = 0;
		while (x_tmp < 200)
		{
			mini_mlx_pixel_put(&mlx->mini_map, x, y, 0xffffffff);
			x_tmp++;
			x++;
		}
		y_start++;
		y++;
	}
}

void	walls(t_mlx *mlx)
{
	int			i;
	t_coords	coords;

	i = 0;
	coords.x = 0;
	coords.y = 0;
	mlx->wall.rect_width = (WIN_WIDTH / RAYS);
	mlx->wall.distprojplane = (WIN_WIDTH / 2) / tan(FOV / 2);
	while (i < RAYS)
	{
		mlx->rays.distance[i] *= cos(mlx->rays.ray_angle[i] - mlx->p.angle);
		mlx->wall.wall_height = (TILE_SIZE / mlx->rays.distance[i])
			* mlx->wall.distprojplane;
		coords.y = (WIN_HEIGHT / 2) - (mlx->wall.wall_height / 2);
		if (coords.y < 0)
			coords.y = 0;
		draw_ceiling(mlx, coords);
		draw_wall(mlx, coords, i);
		draw_floor(mlx, coords);
		coords.x += mlx->wall.rect_width;
		i++;
	}
}
