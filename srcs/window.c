/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 12:35:35 by aharrass          #+#    #+#             */
/*   Updated: 2023/05/30 01:10:13 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	update(t_mlx *mlx)
{
	double	new_x;
	double	new_y;

	new_x = mlx->p.x;
	new_y = mlx->p.y;
	mlx->p.angle += mlx->p.turn_direction * mlx->p.rot_speed;
	if (mlx->p.angle < 0)
		mlx->p.angle += 2 * M_PI;
	if (mlx->p.angle > 2 * M_PI)
		mlx->p.angle -= 2 * M_PI;
	if (mlx->keys.w == PRESSED)
	{
		new_x += cos(mlx->p.angle) * mlx->p.move_speed;
		new_y += sin(mlx->p.angle) * mlx->p.move_speed;
	}
	if (mlx->keys.s == PRESSED)
	{
		new_x -= cos(mlx->p.angle) * mlx->p.move_speed;
		new_y -= sin(mlx->p.angle) * mlx->p.move_speed;
	}
	if (mlx->keys.a == PRESSED)
	{
		new_x += cos(mlx->p.angle - M_PI_2) * mlx->p.move_speed;
		new_y += sin(mlx->p.angle - M_PI_2) * mlx->p.move_speed;
	}
	if (mlx->keys.d == PRESSED)
	{
		new_x += cos(mlx->p.angle + M_PI_2) * mlx->p.move_speed;
		new_y += sin(mlx->p.angle + M_PI_2) * mlx->p.move_speed;
	}
	if (wall_check_2(new_x, new_y, mlx->map.map))
	{
		mlx->p.x = new_x;
		mlx->p.y = new_y;
	}
	else if (mlx->keys.s == RELEASED)
	{
		new_x = mlx->p.x;
		new_y = mlx->p.y;
		if (mlx->rays.vertical_hit[(RAYS - 1) / 2])
		{
			if (mlx->rays.facing_down[(RAYS - 1) / 2])
				new_y += mlx->p.move_speed;
			else
				new_y -= mlx->p.move_speed;
			if (wall_check_2(new_x, new_y, mlx->map.map))
			{
				mlx->p.x = new_x;
				mlx->p.y = new_y;
			}
		}
		else
		{
			if (mlx->rays.facing_right[(RAYS - 1) / 2])
				new_x += mlx->p.move_speed;
			else
				new_x -= mlx->p.move_speed;
			if (wall_check_2(new_x, new_y, mlx->map.map))
			{
				mlx->p.x = new_x;
				mlx->p.y = new_y;
			}
		}
	}
}

int	render(t_pars *g)
{
	mlx_clear_window(g->mlx.mlx_ptr, g->mlx.win_ptr);
	g->mlx.img = mlx_new_image(g->mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	g->mlx.addr = mlx_get_data_addr(g->mlx.img, &g->mlx.bits_per_pixel,
			&g->mlx.line_length, &g->mlx.endian);
	update(&g->mlx);
	rays(&g->mlx);
	cast_rays(&g->mlx);
	walls(&g->mlx);
	mlx_put_image_to_window(g->mlx.mlx_ptr, g->mlx.win_ptr, g->mlx.img, 0, 0);
	mlx_destroy_image(g->mlx.mlx_ptr, g->mlx.img);
	if (g->mlx.keys.tab % 2 == 0)
	{
		render_mini_map(&g->mlx);
	}
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
	g->mlx.keys.tab = 0;
	map_hightnwidth(&g->mlx.map);
	find_player_pos(&g->mlx.p, &g->mlx.map);
	get_player_ang(&g->mlx.p, g->mlx.map.map);
	g->mlx.win_ptr = mlx_new_window(g->mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
			"cub3d");
	mlx_hook(g->mlx.win_ptr, 2, 0, key_press, g);
	mlx_hook(g->mlx.win_ptr, 3, 0, key_release, g);
	mlx_hook(g->mlx.win_ptr, 6, 0, mouse_hook, &g->mlx);
	mlx_hook(g->mlx.win_ptr, 17, 0, close_window, &g->mlx);
	mlx_loop_hook(g->mlx.mlx_ptr, render, g);
	mlx_loop(g->mlx.mlx_ptr);
}
