/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mham <rel-mham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:18:25 by rel-mham          #+#    #+#             */
/*   Updated: 2023/05/30 18:15:01 by rel-mham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_first_last_wall(t_pars *g, int n)
{
	if (n == -1)
	{
		g->l = n;
		while (g->rgb[++g->l])
		{
			if (this_line(g->rgb[g->l]))
				break ;
		}
	}
	else
	{
		g->l1 = n;
		while (g->rgb[g->l1])
		{
			if (this_line(g->rgb[g->l1]))
				break ;
			g->l1--;
		}
	}
}

void	check_middle_help(t_pars *g, int i, int len)
{
	while (++i < len)
	{
		if (g->rgb[g->l][i] == '0' || g->rgb[g->l][i] == 'E'
			|| g->rgb[g->l][i] == 'W' || g->rgb[g->l][i] == 'N'
			|| g->rgb[g->l][i] == 'S')
		{
			if (i >= (int)ft_strlen(g->rgb[g->l - 1])
				|| i >= (int)ft_strlen(g->rgb[g->l + 1]))
				write_error("Map invalid middle");
			if (g->rgb[g->l - 1][i] == 32 || g->rgb[g->l + 1][i] == 32
				|| g->rgb[g->l][i - 1] == 32 || g->rgb[g->l][i + 1] == 32)
				write_error("Map invalid middle");
		}
	}
}

void	check_middle(t_pars *g)
{
	int	len;
	int	i;

	g->l++;
	while (g->l < g->l1)
	{
		i = 0;
		len = ft_strlen(g->rgb[g->l]) - 1;
		while (g->rgb[g->l][len] == 32)
			len--;
		while (g->rgb[g->l][i] == 32)
			i++;
		if (g->rgb[g->l][i] != '1' || g->rgb[g->l][len] != '1')
			write_error("Left or right wall broken");
		check_middle_help(g, i, len);
		g->l++;
	}
}

void	check_map_char_help(char *s, int i, int *d)
{
	if (s[i] == 'N' || s[i] == 'S' || s[i] == 'E' || s[i] == 'W')
	{
		if (*d == 0)
			(*d)++;
		else
			write_error("Player char repeated");
	}
	else if (s[i] != '0' && s[i] != 32 && s[i] != '1' && s[i] != '\n')
		write_error("Wrong char in map");
	else if (s[i] == '\n' && s[i + 1] == '\n')
		write_error("Double endl");
}

void	check_map_char(char *s)
{
	int	i;
	int	j;
	int	d;

	i = 0;
	j = ft_strlen(s) - 1;
	d = 0;
	while (((s[i] >= 9 && s[i] <= 13) || s[i] == 32) && s[i])
		i++;
	while (((s[i] >= 9 && s[i] <= 13) || s[i] == 32) && j > 0)
		j--;
	if (s[i] == '\0')
		write_error("Invalid map");
	while (i <= j)
	{
		check_map_char_help(s, i, &d);
		i++;
	}
	if (!d)
		write_error("Player missing");
}
