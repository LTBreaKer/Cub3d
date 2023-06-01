/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_window2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 01:09:25 by aharrass          #+#    #+#             */
/*   Updated: 2023/06/01 11:52:51 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	mouse_hook12(int x, int y, t_mlx *mlx)
{
	static int	i;

	(void)y;
	mlx_mouse_hide();
	if (i == 0)
	{
		mlx->keys.old_mouse_x = x;
		i++;
	}
	mlx->keys.mouse_x = x;
	if (mlx->keys.mouse_x > mlx->keys.old_mouse_x)
		mlx->p.angle += 5 * mlx->p.rot_speed / 3;
	else if (mlx->keys.mouse_x < mlx->keys.old_mouse_x)
		mlx->p.angle -= 5 * mlx->p.rot_speed / 3;
	if (mlx->p.angle > 2 * M_PI)
		mlx->p.angle -= 2 * M_PI;
	else if (mlx->p.angle < 0)
		mlx->p.angle += 2 * M_PI;
	mlx->keys.old_mouse_x = mlx->keys.mouse_x;
	if (mlx->keys.mouse_x < 0)
		mlx->keys.old_mouse_x++;
	else if (mlx->keys.mouse_x > WIN_WIDTH)
		mlx->keys.old_mouse_x--;
	return (0);
}

void	fill_end_start(t_coords *start, t_coords *end, t_mlx *mlx)
{
	if ((*end).x > mlx->map.map_width * (TILE_SIZE) / MAP_SCALE)
	{
		(*start).x -= ((*end).x - mlx->map.map_width * (TILE_SIZE) / MAP_SCALE);
		(*end).x = mlx->map.map_width * (TILE_SIZE) / MAP_SCALE;
	}
	if ((*end).y > mlx->map.map_height * (TILE_SIZE) / MAP_SCALE)
	{
		(*start).y -= (*end).y - (mlx->map.map_height * TILE_SIZE / MAP_SCALE);
		(*end).y = mlx->map.map_height * (TILE_SIZE) / MAP_SCALE;
	}
	if ((*start).x < 0)
	{
		(*end).x -= (*start).x;
		(*start).x = 0;
	}
	if ((*start).y < 0)
	{
		(*end).y -= (*start).y;
		(*start).y = 0;
	}
	if ((*end).x > mlx->map.map_width * (TILE_SIZE) / MAP_SCALE)
		(*end).x = mlx->map.map_width * (TILE_SIZE) / MAP_SCALE;
	if ((*end).y > mlx->map.map_height * (TILE_SIZE) / MAP_SCALE)
		(*end).y = mlx->map.map_height * (TILE_SIZE) / MAP_SCALE;
}

void	fill_mini_map(t_mlx *mlx, t_coords *co, t_coords *start, t_coords *end)
{
	int	x_tmp;

	fill_end_start(start, end, mlx);
	while ((*start).y < (*end).y && (*co).y < 200)
	{
		x_tmp = (*start).x;
		(*co).x = 0;
		while (x_tmp < (*end).x && (*co).x < 200)
		{
			mini_mlx_pixel_put(&mlx->mini_map, (*co).x, (*co).y,
				get_map_color(&mlx->map, x_tmp, (*start).y));
			x_tmp++;
			(*co).x++;
		}
		while (x_tmp < 200)
		{
			mini_mlx_pixel_put(&mlx->mini_map, (*co).x, (*co).y, 0xffffffff);
			x_tmp++;
			(*co).x++;
		}
		(*start).y++;
		(*co).y++;
	}
}

void	crop_map(t_mlx *mlx)
{
	t_coords	co;
	t_coords	start;
	t_coords	end;
	int			x_tmp;

	co.x = 0;
	co.y = 0;
	start.x = (mlx->p.x / MAP_SCALE) - 100;
	start.y = (mlx->p.y / MAP_SCALE) - 100;
	end.x = (mlx->p.x / MAP_SCALE) + 100;
	end.y = (mlx->p.y / MAP_SCALE) + 100;
	fill_mini_map(mlx, &co, &start, &end);
	while (start.y < 200)
	{
		x_tmp = start.x;
		co.x = 0;
		while (x_tmp < 200)
		{
			mini_mlx_pixel_put(&mlx->mini_map, co.x, co.y, 0xffffffff);
			x_tmp++;
			co.x++;
		}
		start.y++;
		co.y++;
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
