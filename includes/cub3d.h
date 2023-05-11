/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:16:03 by rel-mham          #+#    #+#             */
/*   Updated: 2023/05/11 08:55:54 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/libft.h"
# include "../minilibx_opengl_20191021/mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define TILE_SIZE 32
# define W_KEY 13
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define ESC 53
# define LEFT_ARR 123
# define RIGHT_ARR 124
# define POINT_SIZE 10
# define PRESSED 1
# define RELEASED 0
# define LEFT -1
# define RIGHT 1
# define RAYS (1280 / 25)
# define FOV (60 * (M_PI / 180))

typedef struct s_rays
{
	double	ray_angle[RAYS];
	double	wall_hit_x;
	double	wall_hit_y;
	double	distance;
}			t_rays;

typedef struct s_coords
{
	double	x;
	double	y;
}			t_coords;

typedef struct s_p
{
	double	x;
	double	y;
	double	angle;
	double	move_speed;
	double	rot_speed;
	int		turn_direction;
}			t_p;

typedef struct s_keys
{
	int		w;
	int		a;
	int		s;
	int		d;
	int		left;
	int		right;
}			t_keys;

typedef struct s_map
{
	char	**map;
	int		wall_color;
	int		floor_color;

}			t_map;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_p		p;
	t_keys	keys;
	t_map	map;
	t_rays	rays;
}			t_mlx;

typedef struct s_pars
{
	char	**rgb;
	char	*hash;
	char	*line;
	int		l;
	int		l1;
	int		fd;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f;
	int		c;
	t_mlx	mlx;
}			t_pars;

char		*get_next_line(int fd);
char		*gnl_strjoin(char *s1, char const *s2);
int			first_elem(t_pars *g);
int			second_elem(t_pars *g, char *s, int n);
void		valid_rgb(t_pars *g);
void		check_rgb(t_pars *g, char c);
int			valid_line(t_pars *g);
void		write_error(char *str);
void		loopars(t_pars *g);

//--------------------window.c--------------------

void		draw_point(t_mlx *ptr, t_coords coords, int size, int color);
void		draw_circle(t_mlx *mlx, t_coords coords, int radius, int color);
void		draw_line(t_mlx *mlx, t_coords coords, double angle, int color);
int			wall_check(double new_x, double new_y, char **map);
void		manage_window(t_pars *g);
#endif