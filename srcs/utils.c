/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 01:06:06 by aharrass          #+#    #+#             */
/*   Updated: 2023/05/30 01:07:02 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	wall_check(double new_x, double new_y, char **map)
{
	int	tile_x;
	int	tile_y;

	tile_x = floor(new_x / TILE_SIZE);
	tile_y = floor(new_y / TILE_SIZE);
	if (tile_y < (int)ft_double_strlen(map)
		&& tile_x < (int)ft_strlen(map[tile_y]) && map[tile_y][tile_x] == '1')
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
		&& tile_x < (int)ft_strlen(map[tile_y]) && map[tile_y][tile_x] == '1')
		return (0);
	tile_x = floor((new_x + TILE_SIZE / 12) / TILE_SIZE);
	if (tile_y < (int)ft_double_strlen(map)
		&& tile_x < (int)ft_strlen(map[tile_y]) && map[tile_y][tile_x] == '1')
		return (0);
	tile_x = floor((new_x - TILE_SIZE / 12) / TILE_SIZE);
	if (tile_y < (int)ft_double_strlen(map)
		&& tile_x < (int)ft_strlen(map[tile_y]) && map[tile_y][tile_x] == '1')
		return (0);
	tile_y = floor((new_y + TILE_SIZE / 12) / TILE_SIZE);
	if (tile_y < (int)ft_double_strlen(map)
		&& tile_x < (int)ft_strlen(map[tile_y]) && map[tile_y][tile_x] == '1')
		return (0);
	tile_y = floor((new_y - TILE_SIZE / 12) / TILE_SIZE);
	if (tile_y < (int)ft_double_strlen(map)
		&& tile_x < (int)ft_strlen(map[tile_y]) && map[tile_y][tile_x] == '1')
		return (0);
	return (1);
}

void	map_hightnwidth(t_map *map)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	j = 0;
	tmp = 0;
	map->map_height = ft_double_strlen(map->map);
	map->map_width = 0;
	while (map->map[i])
	{
		tmp = ft_strlen(map->map[i]);
		if (tmp > map->map_width)
			map->map_width = tmp;
		i++;
	}
}

int	get_map_color(t_map *map, int x, int y)
{
	char	*dst;

	dst = map->addr + (y * map->line_length + x * (map->bpp / 8));
	return (*(unsigned int *)dst);
}

void	get_player_ang(t_p *p, char **map)
{
	int	tmp_x;
	int	tmp_y;

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
