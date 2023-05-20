/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 12:35:35 by aharrass          #+#    #+#             */
/*   Updated: 2023/05/20 17:24:47 by aharrass         ###   ########.fr       */
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

void	ray_direction(t_rays *rays, int i)
{
	rays->facing_down = rays->ray_angle[i] > 0 && rays->ray_angle[i] < M_PI;
	rays->facing_up = !rays->facing_down;
	rays->facing_right = rays->ray_angle[i] < M_PI / 2 || rays->ray_angle[i] > 3 * M_PI / 2;
	rays->facing_left = !rays->facing_right;
}

void	corr_steps(t_rays rays, double *xstep, double *ystep)
{
	if (rays.facing_up && *ystep > 0)
		*ystep *= -1;
	else if (rays.facing_down && *ystep < 0)
		*ystep *= -1;
	if (rays.facing_right && *xstep < 0)
		*xstep *= -1;
	else if (rays.facing_left && *xstep > 0)
		*xstep *= -1;
}

int	horizontal_inter(t_mlx *mlx, t_coords *hor_inter, int i)
{
	double xstep;
	double ystep;

	if (mlx->rays.ray_angle[i] == 0 || mlx->rays.ray_angle[i] == M_PI
		|| mlx->rays.ray_angle[i] == 2 * M_PI)
		return (hor_inter->x = 0, hor_inter->y = 0, 1);
	ray_direction(&mlx->rays, i);
	hor_inter->y = floor(mlx->p.y / TILE_SIZE) * TILE_SIZE;
	if (mlx->rays.facing_down)
		hor_inter->y += TILE_SIZE;
	hor_inter->x = mlx->p.x + (hor_inter->y - mlx->p.y) / tan(mlx->rays.ray_angle[i]);
	if (hor_inter->x < 0 || floor(hor_inter->x / TILE_SIZE) >= ft_strlen(mlx->map.map[(int)floor(hor_inter->y / TILE_SIZE)]))
				return (hor_inter->x = 0, hor_inter->y = 0, 1);
	if (hor_inter->y < 0 || floor(hor_inter->y / TILE_SIZE) >= ft_double_strlen(mlx->map.map))
				return (hor_inter->x = 0, hor_inter->y = 0, 1);
	ystep = TILE_SIZE;
	xstep = TILE_SIZE / tan(mlx->rays.ray_angle[i]);
	corr_steps(mlx->rays, &xstep, &ystep);
	while (hor_inter->x >= 0 && hor_inter->y >= 0
		&& floor(hor_inter->y / TILE_SIZE) < ft_double_strlen(mlx->map.map)
		&& floor(hor_inter->x / TILE_SIZE) < ft_strlen(mlx->map.map[(int)floor(hor_inter->y / TILE_SIZE)]))
	{
		if (mlx->rays.facing_up)
			hor_inter->y--;
		if (wall_check(hor_inter->x, hor_inter->y, mlx->map.map) == 0)
		{
			if (mlx->rays.facing_up)
				hor_inter->y++;
			break;
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
	double xstep;
	double ystep;

	if (mlx->rays.ray_angle[i] == M_PI / 2 || mlx->rays.ray_angle[i] == 3 * M_PI / 2)
		return (ver_inter->x = 0, ver_inter->y = 0, 1);
	ray_direction(&mlx->rays, i);
	ver_inter->x = floor(mlx->p.x / TILE_SIZE) * TILE_SIZE;
	if (mlx->rays.facing_right)
		ver_inter->x += TILE_SIZE;
	ver_inter->y = mlx->p.y + (ver_inter->x - mlx->p.x) * tan(mlx->rays.ray_angle[i]);
	if (ver_inter->y < 0 || floor(ver_inter->y / TILE_SIZE) >= ft_double_strlen(mlx->map.map))
		return (ver_inter->x = 0, ver_inter->y = 0, 1);
	if (ver_inter->x < 0 || floor(ver_inter->x / TILE_SIZE) >= ft_strlen(mlx->map.map[(int)floor(ver_inter->y / TILE_SIZE)]))
		return (ver_inter->x = 0, ver_inter->y = 0, 1);
	xstep = TILE_SIZE;
	ystep = TILE_SIZE * tan(mlx->rays.ray_angle[i]);
	corr_steps(mlx->rays, &xstep, &ystep);
	while (ver_inter->x >= 0 && ver_inter->y >= 0
		&& floor(ver_inter->y / TILE_SIZE) < ft_double_strlen(mlx->map.map)
		&& floor(ver_inter->x / TILE_SIZE) < ft_strlen(mlx->map.map[(int)floor(ver_inter->y / TILE_SIZE)]))
	{
		if (mlx->rays.facing_left)
			ver_inter->x--;
		if (wall_check(ver_inter->x, ver_inter->y, mlx->map.map) == 0)
		{
			if (mlx->rays.facing_left)
				ver_inter->x++;	
			break;
		}
		else
		{			
			ver_inter->x += xstep;
			ver_inter->y += ystep;
		}
	}
	return (0);
}

void	cast_rays(t_mlx *mlx)
{
	int i;
	t_coords hor_inter[RAYS];
	t_coords ver_inter[RAYS];
	double	hor_dist;
	double	ver_dist;
	(void)ver_inter;
	
	hor_dist = DBL_MAX;
	ver_dist = DBL_MAX;
	i = 0;
	while (i < RAYS)
	{
		if (horizontal_inter(mlx, &hor_inter[i], i) == 0)
			hor_dist = sqrt(pow(hor_inter[i].x - mlx->p.x, 2) + pow(hor_inter[i].y - mlx->p.y, 2));
		if (vertical_inter(mlx, &ver_inter[i], i) == 0)
			ver_dist = sqrt(pow(ver_inter[i].x - mlx->p.x, 2) + pow(ver_inter[i].y - mlx->p.y, 2));
		if (hor_dist < ver_dist)
		{
			mlx->rays.distance[i] = hor_dist;
			mlx->rays.wall_hit_x[i] = hor_inter[i].x;
			mlx->rays.wall_hit_y[i] = hor_inter[i].y;
		}
		else
		{
			mlx->rays.distance[i] = ver_dist;
			mlx->rays.wall_hit_x[i] = ver_inter[i].x;
			mlx->rays.wall_hit_y[i] = ver_inter[i].y;
		}
		i++;
	}
}

void	rays(t_mlx *mlx)
{
	double	ray_angle;
	int	i;
	
	i = 0;
	ray_angle = mlx->p.angle - FOV / 2;
	while (i < RAYS)
	{
		mlx->rays.ray_angle[i] = ray_angle;
		if (mlx->rays.ray_angle[i] < 0)
			mlx->rays.ray_angle[i] += 2 * M_PI;
		if (mlx->rays.ray_angle[i] > 2 * M_PI)
			mlx->rays.ray_angle[i] -= 2 * M_PI;
		//draw_line(mlx, i);
		ray_angle += (FOV / RAYS);
		i++;
	}
}

void	render_player(t_mlx *mlx)
{
	draw_player(mlx, (t_coords){mlx->p.x / MAP_SCALE, mlx->p.y / MAP_SCALE},
		(TILE_SIZE / MAP_SCALE) /3, 0xFF0000);
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
				draw_point(mlx, (t_coords){tilex,
					tiley}, TILE_SIZE / MAP_SCALE,
					mlx->map.ceiling_color);
			else if (mlx->map.map[y][x] == '0' || mlx->map.map[y][x] == 'N'
					|| mlx->map.map[y][x] == 'S' || mlx->map.map[y][x] == 'E'
					|| mlx->map.map[y][x] == 'W')
				draw_point(mlx, (t_coords){tilex + 1,
					tiley + 1}, TILE_SIZE / MAP_SCALE - 1,
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
	p->move_speed = 3.0;
	p->rot_speed = 4.0 * (M_PI / 180);
	y = 0;
	while (map->map[y])
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
		y++;
	}
}

int	wall_check(double new_x, double new_y, char **map)
{
	int	tile_x;
	int	tile_y;

	tile_x = floor(new_x / TILE_SIZE);
	tile_y = floor(new_y / TILE_SIZE);
	if (tile_y < (int)ft_double_strlen(map)
		&& tile_x < (int)ft_strlen(map[tile_y])
		&& map[tile_y][tile_x] == '1')
		return (0);
	return (1);
}

int	wall_check_2(double new_x, double new_y, char **map)
{
	int	tile_x;
	int	tile_y;

	tile_x = floor(new_x / TILE_SIZE);
	tile_y = floor(new_y / TILE_SIZE);
	if (tile_y < (int)ft_double_strlen(map)
		&& tile_x < (int)ft_strlen(map[tile_y])
		&& map[tile_y][tile_x] == '1')
		return (0);
	tile_x = floor((new_x + TILE_SIZE / 12) / TILE_SIZE);
	if (tile_y < (int)ft_double_strlen(map)
		&& tile_x < (int)ft_strlen(map[tile_y])
		&& map[tile_y][tile_x] == '1')
		return (0);
	tile_x = floor((new_x - TILE_SIZE / 12) / TILE_SIZE);
	if (tile_y < (int)ft_double_strlen(map)
		&& tile_x < (int)ft_strlen(map[tile_y])
		&& map[tile_y][tile_x] == '1')
		return (0);
	tile_y = floor((new_y + TILE_SIZE / 12) / TILE_SIZE);
	if (tile_y < (int)ft_double_strlen(map)
		&& tile_x < (int)ft_strlen(map[tile_y])
		&& map[tile_y][tile_x] == '1')
		return (0);
	tile_y = floor((new_y - TILE_SIZE / 12) / TILE_SIZE);
	if (tile_y < (int)ft_double_strlen(map)
		&& tile_x < (int)ft_strlen(map[tile_y])
		&& map[tile_y][tile_x] == '1')
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
	if (wall_check_2(new_x, new_y, g->mlx.map.map))
	{
		g->mlx.p.x = new_x;
		g->mlx.p.y = new_y;
	}
}

void walls(t_mlx *mlx)
{
	int	i;
	t_coords	coords;

	i = 0;
	coords.x = 0;
	coords.y = 0;
	mlx->wall.rect_width = (WIN_WIDTH / RAYS);
	mlx->wall.distprojplane = (WIN_WIDTH / 2) / tan(FOV / 2);
	while (i < RAYS)
	{
		mlx->rays.distance[i] *= cos(mlx->rays.ray_angle[i] - mlx->p.angle);
		mlx->wall.wall_height = (TILE_SIZE / mlx->rays.distance[i]) * mlx->wall.distprojplane;
		if (mlx->wall.wall_height > WIN_HEIGHT)
			mlx->wall.wall_height = WIN_HEIGHT;
		coords.y = (WIN_HEIGHT / 2) - (mlx->wall.wall_height / 2);
		draw_ceiling(mlx, coords);
		draw_wall(mlx, coords);
		draw_floor(mlx, coords);
		coords.x += mlx->wall.rect_width;
		i++;
	}
}

int	render(t_pars *g)
{
	mlx_clear_window(g->mlx.mlx_ptr, g->mlx.win_ptr);
	g->mlx.img = mlx_new_image(g->mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	g->mlx.addr = mlx_get_data_addr(g->mlx.img, &g->mlx.bits_per_pixel,
										&g->mlx.line_length, &g->mlx.endian);
	update(g);
	rays(&g->mlx);
	cast_rays(&g->mlx);
	walls(&g->mlx);
	render_map(&g->mlx);
	render_player(&g->mlx);
	mlx_put_image_to_window(g->mlx.mlx_ptr, g->mlx.win_ptr, g->mlx.img, 0, 0);
	mlx_destroy_image(g->mlx.mlx_ptr, g->mlx.img);
	return (0);
}

void  get_player_ang(t_p *p, char **map)
{
	int tmp_x;
	int tmp_y;

	tmp_x = floor((p->x - TILE_SIZE / 2) / TILE_SIZE);
	tmp_y = floor((p->y - TILE_SIZE / 2) / TILE_SIZE);
	if (map[tmp_y][tmp_x] == 'N')
		p->angle = 3 * M_PI / 2;
	else if (map[tmp_y][tmp_x] == 'S')
		p->angle = M_PI / 2;
	else if (map[tmp_y][tmp_x] == 'W')
		p->angle = M_PI;
	else if (map[tmp_y][tmp_x] == 'E')
		p->angle = 0;
}

int	mouse_hook(int x, int y, t_mlx *mlx)
{
	(void)mlx;
	(void)y; // -100, 2779
	// mlx_mouse_hide();
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

void	manage_window(t_pars *g)
{
	g->mlx.map.map = g->rgb;
	g->mlx.map.floor_color = g->f;
	g->mlx.map.ceiling_color = g->c;
	g->mlx.p.turn_direction = 0;
	g->mlx.keys.w = 0;
	g->mlx.keys.s = 0;
	g->mlx.keys.a = 0;
	g->mlx.keys.d = 0;
	find_player_pos(&g->mlx.p, &g->mlx.map);
	get_player_ang(&g->mlx.p, g->mlx.map.map);
	g->mlx.mlx_ptr = mlx_init();
	g->mlx.win_ptr = mlx_new_window(g->mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
			"cub3d");
	mlx_hook(g->mlx.win_ptr, 2, 0, key_press, g);
	mlx_hook(g->mlx.win_ptr, 3, 0, key_release, g);
	mlx_hook(g->mlx.win_ptr, 6, 0, mouse_hook, &g->mlx);
	mlx_hook(g->mlx.win_ptr, 17, 0, close_window, &g->mlx);
	mlx_loop_hook(g->mlx.mlx_ptr, render, g);
	mlx_loop(g->mlx.mlx_ptr); 
}
