/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 21:01:29 by aharrass          #+#    #+#             */
/*   Updated: 2023/05/30 00:35:36 by aharrass         ###   ########.fr       */
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
