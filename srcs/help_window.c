/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 00:49:18 by aharrass          #+#    #+#             */
/*   Updated: 2023/05/31 00:41:11 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	close_window(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->win);
	exit(0);
}

int	key_press(int keycode, t_pars *g)
{
	if (keycode == ESC)
		close_window(&g->mlx);
	if (keycode == TAB_KEY)
		g->mlx.keys.tab += 1;
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
	if (rays->ray_angle[i] > 0 && rays->ray_angle[i] < M_PI)
		rays->facing_down[i] = 1;
	else
		rays->facing_down[i] = 0;
	rays->facing_up[i] = !rays->facing_down[i];
	if (rays->ray_angle[i] < M_PI / 2 || rays->ray_angle[i] > 3 * M_PI / 2)
		rays->facing_right[i] = 1;
	else
		rays->facing_right[i] = 0;
	rays->facing_left[i] = !rays->facing_right[i];
}

void	corr_steps(t_rays rays, double *xstep, double *ystep, int i)
{
	if (rays.facing_up[i] && *ystep > 0)
		*ystep *= -1;
	else if (rays.facing_down[i] && *ystep < 0)
		*ystep *= -1;
	if (rays.facing_right[i] && *xstep < 0)
		*xstep *= -1;
	else if (rays.facing_left[i] && *xstep > 0)
		*xstep *= -1;
}
