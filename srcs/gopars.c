/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gopars.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mham <rel-mham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:25:04 by rel-mham          #+#    #+#             */
/*   Updated: 2023/05/30 17:41:17 by rel-mham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	first_elem(t_pars *g)
{
	char	*tmp;

	tmp = g->line;
	while (*tmp == 32)
		tmp++;
	if (!ft_strncmp(tmp, "NO ", 3) && g->hash[0] != 'd')
		return (g->l++, 0);
	else if (!ft_strncmp(tmp, "WE ", 3) && g->hash[1] != 'd')
		return (g->l++, 1);
	else if (!ft_strncmp(tmp, "EA ", 3) && g->hash[2] != 'd')
		return (g->l++, 2);
	else if (!ft_strncmp(tmp, "SO ", 3) && g->hash[3] != 'd')
		return (g->l++, 3);
	else if (!ft_strncmp(tmp, "F ", 2) && g->hash[4] != 'd')
		return (g->l++, 4);
	else if (!ft_strncmp(tmp, "C ", 2) && g->hash[5] != 'd')
		return (g->l++, 5);
	return (-1);
}

void	get_img(int tx_id, t_pars *g, char *sub)
{
	g->mlx.tx[tx_id].img = mlx_xpm_file_to_image(g->mlx.mlx_ptr, sub,
			&g->mlx.tx[tx_id].width, &g->mlx.tx[tx_id].height);
	if (!g->mlx.tx[tx_id].img)
		write_error("Texture not valid");
	g->mlx.tx[tx_id].addr = mlx_get_data_addr(g->mlx.tx[tx_id].img,
			&g->mlx.tx[tx_id].bpp,
			&g->mlx.tx[tx_id].line_length,
			&g->mlx.tx[tx_id].endian);
}

int	second_elem(t_pars *g, char *s, int n)
{
	char	*sub;
	int		start;
	int		end;

	end = ft_strlen2(s) - 1;
	start = 0;
	while (s[start] == 32)
		start++;
	start += 2;
	while (s[start] == 32)
		start++;
	while (s[end] == 32)
		end--;
	sub = ft_substr(s, start, end - start + 1);
	if (n == 0)
		get_img(NO, g, sub);
	else if (n == 1)
		get_img(WE, g, sub);
	else if (n == 2)
		get_img(EA, g, sub);
	else if (n == 3)
		get_img(SO, g, sub);
	free(sub);
	return (1);
}

void	valid_rgb(t_pars *g)
{
	char	*tmp;
	char	c;
	int		i;

	tmp = g->line;
	while (*tmp == 32)
		tmp++;
	c = *tmp;
	tmp += 1;
	while (*tmp == 32)
		tmp++;
	i = 0;
	if (count_char(tmp, ',') != 2)
		write_error("More or less than 2 comma");
	while (tmp[i] != '\n')
	{
		if (tmp[i] != ',' && tmp[i] != 32 && (tmp[i] < '0' || tmp[i] > '9'))
			write_error("Not valid RGB 1");
		i++;
	}
	g->rgb = ft_split(tmp, ',');
	if (ft_double_strlen(g->rgb) != 3)
		write_error("Not valid RGB 2");
	check_rgb(g, c);
}

int	valid_line(t_pars *g)
{
	int	ret;
	int	i;

	i = 0;
	while (g->line[i] == 32)
		i++;
	if (g->line[i] == '\n')
		return (-2);
	ret = first_elem(g);
	if (ret >= 0 && ret <= 3)
	{
		if (!second_elem(g, g->line, ret))
			write_error("Texture not valid");
		return (ret);
	}
	else if (ret == 4 || ret == 5)
	{
		valid_rgb(g);
		return (ret);
	}
	return (-1);
}
