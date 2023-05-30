/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 00:57:21 by aharrass          #+#    #+#             */
/*   Updated: 2023/05/30 01:15:07 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	render_mini_map(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	mlx->map.img = mlx_new_image(mlx->mlx_ptr, mlx->map.map_width * (TILE_SIZE)
			/ MAP_SCALE, mlx->map.map_height * (TILE_SIZE) / MAP_SCALE);
	mlx->map.addr = mlx_get_data_addr(mlx->map.img, &mlx->map.bpp,
			&mlx->map.line_length, &mlx->map.endian);
	mlx->mini_map.img = mlx_new_image(mlx->mlx_ptr, 200, 200);
	mlx->mini_map.addr = mlx_get_data_addr(mlx->mini_map.img,
			&mlx->mini_map.bpp, &mlx->mini_map.line_length,
			&mlx->mini_map.endian);
	render_map(mlx);
	render_player(mlx);
	crop_map(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->mini_map.img, 20,
		20);
	mlx_destroy_image(mlx->mlx_ptr, mlx->mini_map.img);
	mlx_destroy_image(mlx->mlx_ptr, mlx->map.img);
}

void	render_player(t_mlx *mlx)
{
	draw_player(mlx, (t_coords){mlx->p.x / MAP_SCALE, mlx->p.y / MAP_SCALE},
		(TILE_SIZE / MAP_SCALE) / 3, 0xFF0000);
	draw_direc(mlx);
}

void	render_map(t_mlx *mlx)
{
	int	x;
	int	y;
	int	tilex;
	int	tiley;

	y = 0;
	tilex = 0;
	tiley = 0;
	while (mlx->map.map[y])
	{
		x = 0;
		while (mlx->map.map[y][x])
		{
			tilex = x * TILE_SIZE / MAP_SCALE;
			tiley = y * TILE_SIZE / MAP_SCALE;
			if (mlx->map.map[y][x] == '1')
				draw_point(mlx, (t_coords){tilex, tiley}, TILE_SIZE / MAP_SCALE,
					mlx->map.ceiling_color);
			else if (mlx->map.map[y][x] == '0' || mlx->map.map[y][x] == 'N'
					|| mlx->map.map[y][x] == 'S' || mlx->map.map[y][x] == 'E'
					|| mlx->map.map[y][x] == 'W')
				draw_point(mlx, (t_coords){tilex + 1, tiley + 1}, TILE_SIZE
					/ MAP_SCALE - 1, 0X55ffffff);
			else
				draw_point(mlx, (t_coords){tilex, tiley}, TILE_SIZE / MAP_SCALE,
					0Xffffffff);
			x++;
		}
		y++;
		if (x < mlx->map.map_width)
		{
			while (x < mlx->map.map_width)
			{
				tilex = x * TILE_SIZE / MAP_SCALE;
				draw_point(mlx, (t_coords){tilex, tiley}, TILE_SIZE / MAP_SCALE,
					0Xffffffff);
				x++;
			}
		}
	}
}

void	find_player_pos(t_p *p, t_map *map)
{
	int	x;
	int	y;

	p->x = 0;
	p->y = 0;
	p->move_speed = 3.0;
	p->rot_speed = 1.5 * (M_PI / 180);
	y = -1;
	while (map->map[++y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (map->map[y][x] == 'N' || map->map[y][x] == 'S'
				|| map->map[y][x] == 'E' || map->map[y][x] == 'W')
			{
				p->x = x * TILE_SIZE + TILE_SIZE / 2;
				p->y = y * TILE_SIZE + TILE_SIZE / 2;
				break ;
			}
			x++;
		}
		if (p->x != 0 && p->y != 0)
			break ;
	}
}
