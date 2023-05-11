/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 12:35:35 by aharrass          #+#    #+#             */
/*   Updated: 2023/05/11 14:18:09 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	close_window(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	exit(0);
}

int	key_press(int keycode, t_pars *g)
{
	if (keycode == ESC)
		close_window(&g->mlx);
	if (keycode == W_KEY)
		g->mlx.keys.w = PRESSED;
	if (keycode == A_KEY)
		g->mlx.keys.a = PRESSED;
	if (keycode == S_KEY)
		g->mlx.keys.s = PRESSED;
	if (keycode == D_KEY)
		g->mlx.keys.d = PRESSED;
	if (keycode == LEFT_ARR)
		g->mlx.p.turn_direction = -1;
	if (keycode == RIGHT_ARR)
		g->mlx.p.turn_direction = 1;
	return (0);
}

int	key_release(int keycode, t_pars *g)
{
	if (keycode == W_KEY)
		g->mlx.keys.w = RELEASED;
	if (keycode == A_KEY)
		g->mlx.keys.a = RELEASED;
	if (keycode == S_KEY)
		g->mlx.keys.s = RELEASED;
	if (keycode == D_KEY)
		g->mlx.keys.d = RELEASED;
	if (keycode == LEFT_ARR)
		g->mlx.p.turn_direction = 0;
	if (keycode == RIGHT_ARR)
		g->mlx.p.turn_direction = 0;
	return (0);
}

void	horizontal_inter(t_mlx *mlx, t_coords *hor_inter)
{
	double xstep;
	double ystep;
	int		i;
	
	i = 0;
	while (i < 1)
	{
		if (mlx->rays.ray_angle[i] == 0 || mlx->rays.ray_angle[i] == M_PI || mlx->rays.ray_angle[i] == 2 * M_PI)
		{
			i++;
			continue ;
		}
		hor_inter->y = floor(mlx->p.y / TILE_SIZE) * TILE_SIZE;
		if (mlx->rays.ray_angle[i] > 0 && mlx->rays.ray_angle[i] < M_PI)
			hor_inter->y += TILE_SIZE;
		hor_inter->x = mlx->p.x + (hor_inter->y - mlx->p.y) / tan(mlx->rays.ray_angle[i]);
		ystep = TILE_SIZE;
		xstep = TILE_SIZE / tan(mlx->rays.ray_angle[i]);
		if (mlx->rays.ray_angle[i] > M_PI / 2 && mlx->rays.ray_angle[i] < 3 * M_PI / 2 && xstep > 0)
			xstep *= -1;
		else if ((mlx->rays.ray_angle[i] < M_PI / 2 || mlx->rays.ray_angle[i] > 3 * M_PI / 2) && xstep < 0)
			xstep *= -1;
		if (mlx->rays.ray_angle[i] > M_PI && mlx->rays.ray_angle[i] < 2 * M_PI && ystep > 0)
			ystep *= -1;
		else if (mlx->rays.ray_angle[i] < M_PI && mlx->rays.ray_angle[i] > 0 && ystep < 0)
			ystep *= -1;
		printf("xstep = %f, ystep = %f\n", xstep, ystep);
		if (hor_inter->x < 0 || hor_inter->x > WIN_WIDTH || hor_inter->y < 0 || hor_inter->y > WIN_HEIGHT)
		{
			return ;
		}
		while (hor_inter->x >= 0 && hor_inter->x <= WIN_WIDTH
			&& hor_inter->y >= 0 && hor_inter->y <= WIN_HEIGHT)
		{
			draw_point(mlx, (t_coords){hor_inter->x + TILE_SIZE / 2, hor_inter->y + TILE_SIZE / 3},
				TILE_SIZE / 3, 0x00FF00);
			printf("------------------------\n");
			printf("x = %f, y = %f\n", floor(hor_inter->x / TILE_SIZE), floor(hor_inter->y / TILE_SIZE));
			if (wall_check(hor_inter->x, hor_inter->y, mlx->map.map))
			{
				hor_inter->x += xstep;
				hor_inter->y += ystep;
			}
			else
				return ;
		}
		i++;
	}
}

void	cast_rays(t_mlx *mlx)
{
	t_coords hor_inter;
	
	horizontal_inter(mlx, &hor_inter);
	// hor_inter.x += TILE_SIZE / 2;
	// hor_inter.y += TILE_SIZE / 2;
	// draw_point(mlx, hor_inter, TILE_SIZE / 3, 0x00FF00);
}

void	rays(t_mlx *mlx)
{
	double	ray_angle;
	int	i;
	
	i = 0;
	ray_angle = mlx->p.angle - FOV / 2;
	while (i < 1)
	{
		mlx->rays.ray_angle[i] = ray_angle;
		if (mlx->rays.ray_angle[i] < 0)
			mlx->rays.ray_angle[i] += 2 * M_PI;
		if (mlx->rays.ray_angle[i] > 2 * M_PI)
			mlx->rays.ray_angle[i] -= 2 * M_PI;
		// printf("x = %f\n", mlx->p.x);
		// printf("y = %f\n", mlx->p.y);
		draw_line(mlx, (t_coords){mlx->p.x + TILE_SIZE - TILE_SIZE / 3, mlx->p.y
		+ TILE_SIZE - TILE_SIZE / 3}, mlx->rays.ray_angle[i], 0X1d53aa);
		ray_angle += (FOV / RAYS);
		i++;
	}
}

void	render_player(t_mlx *mlx)
{
	draw_point(mlx, (t_coords){mlx->p.x + TILE_SIZE / 2 + TILE_SIZE
		/ 12, mlx->p.y + TILE_SIZE / 2 + TILE_SIZE / 12},
		TILE_SIZE / 3, 0xFF0000);
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
			tilex = x * TILE_SIZE;
			tiley = y * TILE_SIZE;
			if (mlx->map.map[y][x] == '1')
				draw_point(mlx, (t_coords){tilex + TILE_SIZE / 2,
					tiley + TILE_SIZE / 2}, TILE_SIZE,
					mlx->map.wall_color);
			else if (mlx->map.map[y][x] == '0' || mlx->map.map[y][x] == 'N'
					|| mlx->map.map[y][x] == 'S' || mlx->map.map[y][x] == 'E'
					|| mlx->map.map[y][x] == 'W')
				draw_point(mlx, (t_coords){tilex + TILE_SIZE / 2 + 1,
					tiley + TILE_SIZE / 2 + 1}, TILE_SIZE - 1,
					0Xffffff);
			x++;
		}
		y++;
	}
}

void	find_player_pos(t_p *p, t_map *map)
{
	int	x;
	int	y;

	p->x = 0;
	p->y = 0;
	p->move_speed = 5.0;
	p->rot_speed = 15.0 * (M_PI / 180);
	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (map->map[y][x] == 'N')
			{
				p->x = x * TILE_SIZE + TILE_SIZE / 4;
				p->y = y * TILE_SIZE + TILE_SIZE / 4;
				break ;
			}
			x++;
		}
		if (p->x != 0 && p->y != 0)
			break ;
		y++;
	}
}

int	wall_check(double new_x, double new_y, char **map)
{
	int	tile_x;
	int	tile_y;

	tile_x = floor(new_x / TILE_SIZE);
	tile_y = floor(new_y / TILE_SIZE);
	if (tile_y < (int)ft_double_strlen(map) && tile_x < (int)ft_strlen(map[tile_y]) && map[tile_y][tile_x] == '1')
		return (0);
	tile_x = (new_x + TILE_SIZE / 3 - 1) / TILE_SIZE;
	if (tile_y < (int)ft_double_strlen(map) && tile_x < (int)ft_strlen(map[tile_y]) &&map[tile_y][tile_x] == '1')
		return (0);
	tile_y = (new_y + TILE_SIZE / 3 - 1) / TILE_SIZE;
	if (tile_y < (int)ft_double_strlen(map) && tile_x < (int)ft_strlen(map[tile_y]) &&map[tile_y][tile_x] == '1')
		return (0);
	return (1);
}

void	update(t_pars *g)
{
	double	new_x;
	double	new_y;

	new_x = g->mlx.p.x;
	new_y = g->mlx.p.y;
	g->mlx.p.angle += g->mlx.p.turn_direction * g->mlx.p.rot_speed;
	if (g->mlx.p.angle < 0)
		g->mlx.p.angle += 2 * M_PI;
	if (g->mlx.p.angle > 2 * M_PI)
		g->mlx.p.angle -= 2 * M_PI;
	if (g->mlx.keys.w == PRESSED)
	{
		new_x += cos(g->mlx.p.angle) * g->mlx.p.move_speed;
		new_y += sin(g->mlx.p.angle) * g->mlx.p.move_speed;
	}
	if (g->mlx.keys.s == PRESSED)
	{
		new_x -= cos(g->mlx.p.angle) * g->mlx.p.move_speed;
		new_y -= sin(g->mlx.p.angle) * g->mlx.p.move_speed;
	}
	if (g->mlx.keys.a == PRESSED)
	{
		new_x += cos(g->mlx.p.angle - M_PI_2) * g->mlx.p.move_speed;
		new_y += sin(g->mlx.p.angle - M_PI_2) * g->mlx.p.move_speed;
	}
	if (g->mlx.keys.d == PRESSED)
	{
		new_x += cos(g->mlx.p.angle + M_PI_2) * g->mlx.p.move_speed;
		new_y += sin(g->mlx.p.angle + M_PI_2) * g->mlx.p.move_speed;
	}
	if (wall_check(new_x, new_y, g->mlx.map.map))
	{
		g->mlx.p.x = new_x;
		g->mlx.p.y = new_y;
	}
}

int	render(t_pars *g)
{
	update(g);
	render_map(&g->mlx);
	render_player(&g->mlx);
	rays(&g->mlx);
	cast_rays(&g->mlx);
	return (0);
}

void	manage_window(t_pars *g)
{
	printf("[%f]\n", tan(M_PI / 2));
	g->mlx.map.map = g->rgb;
	g->mlx.map.wall_color = g->f;
	g->mlx.map.floor_color = g->c;
	g->mlx.p.turn_direction = 0;
	g->mlx.p.angle = 3 * M_PI / 2;
	find_player_pos(&g->mlx.p, &g->mlx.map);
	g->mlx.mlx_ptr = mlx_init();
	g->mlx.win_ptr = mlx_new_window(g->mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
			"cub3d");
	mlx_hook(g->mlx.win_ptr, 2, 0, key_press, g);
	mlx_hook(g->mlx.win_ptr, 3, 0, key_release, g);
	mlx_hook(g->mlx.win_ptr, 17, 0, close_window, &g->mlx);
	mlx_loop_hook(g->mlx.mlx_ptr, render, g);
	mlx_loop(g->mlx.mlx_ptr); 
}
