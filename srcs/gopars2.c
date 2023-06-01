/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gopars2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mham <rel-mham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:23:52 by rel-mham          #+#    #+#             */
/*   Updated: 2023/05/30 18:16:45 by rel-mham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	mapars(t_pars *g)
{
	free(g->hash);
	g->hash = NULL;
	while (1)
	{
		g->line = get_next_line(g->fd);
		if (!g->line)
			break ;
		g->hash = gnl_strjoin(g->hash, g->line);
		free(g->line);
	}
	check_map_char(g->hash);
	g->rgb = ft_split(g->hash, '\n');
	check_first_last_wall(g, -1);
	check_first_last_wall(g, ft_double_strlen(g->rgb) - 1);
	check_middle(g);
}

void	loopars(t_pars *g)
{
	int	j;

	while (1)
	{
		if (g->l == 6)
			break ;
		g->line = get_next_line(g->fd);
		if (!g->line)
			break ;
		j = valid_line(g);
		if (j == -1)
			write_error("Not a valid identifier");
		free(g->line);
		if (j == -2)
			continue ;
		if (j >= 0 || j <= 5)
			g->hash[j] = 'd';
	}
	if (g->l < 6 || g->l > 6)
		write_error("Missing data");
}

void	check_rgb(t_pars *g, char c)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (g->rgb[i])
	{
		num = ft_atoi(g->rgb[i]);
		if (num < 0 || num > 255)
			write_error("Not valid RGB");
		i++;
	}
	if (c == 'F')
		g->f = (ft_atoi(g->rgb[0]) * 65536) + (ft_atoi(g->rgb[1]) * 256)
			+ ft_atoi(g->rgb[2]);
	else if (c == 'C')
		g->c = (ft_atoi(g->rgb[0]) * 65536) + (ft_atoi(g->rgb[1]) * 256)
			+ ft_atoi(g->rgb[2]);
	free_splited(g->rgb);
}
