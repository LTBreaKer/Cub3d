/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mham <rel-mham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 19:54:05 by rel-mham          #+#    #+#             */
/*   Updated: 2023/05/30 14:39:46 by rel-mham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	write_error(char *str)
{
	ft_putendl_fd("Error", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

void	check_ext(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len <= 4 || (str[len - 1] != 'b' || str[len - 2] != 'u' || str[len
				- 3] != 'c' || str[len - 4] != '.'))
	{
		ft_putendl_fd("Error", 2);
		ft_putstr_fd("Not valid extension\n", 2);
		exit(1);
	}
}

void	g_init(t_pars *g)
{
	int	i;

	i = 0;
	g->rgb = NULL;
	g->hash = NULL;
	g->line = NULL;
	g->l = 0;
	g->l1 = 0;
	g->f = 0;
	g->c = 0;
	g->hash = malloc(7);
	g->hash[6] = '\0';
	while (i++ < 6)
		g->hash[i] = 'x';
}

int	this_line(char *s)
{
	int	i;

	i = 0;
	while (s[i] == 32)
		i++;
	if (s[i] == '\0')
		return (0);
	else if (s[i] == '1')
	{
		while (s[i])
		{
			if (s[i] != '1' && s[i] != 32)
				write_error("Up or down invalid wall");
			i++;
		}
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_pars	g;

	if (ac != 2)
		(ft_putstr_fd("Error\nNot valid ARGS\n", 2), exit(1));
	check_ext(av[1]);
	g_init(&g);
	g.fd = open(av[1], O_RDWR);
	if (g.fd < 0)
		write_error("Wrong map path");
	g.mlx.mlx_ptr = mlx_init();
	loopars(&g);
	mapars(&g);
	manage_window(&g);
}
