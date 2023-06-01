/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:16:03 by rel-mham          #+#    #+#             */
/*   Updated: 2023/06/01 11:35:07 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/libft.h"
# include "../minilibx_opengl_20191021/mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <float.h>
# include <limits.h>
# include <math.h>
//# include <mlx.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define TILE_SIZE 60
# define MAP_SCALE 4
# define POINT_SIZE 10
# define PRESSED 1
# define RELEASED 0
# define LEFT -1
# define RIGHT 1
# define RAYS WIN_WIDTH
# define FOV (1.0471975512)

enum
{
	NO,
	SO,
	EA,
	WE,
};

enum			e_keys
{
	W_KEY = 13,
	A_KEY = 0,
	S_KEY = 1,
	D_KEY = 2,
	ESC = 53,
	TAB_KEY = 48,
	LEFT_ARR = 123,
	RIGHT_ARR = 124,
};

typedef struct s_rays
{
	double		ray_angle[RAYS];
	double		distance[RAYS];
	double		wall_hit_x[RAYS];
	double		wall_hit_y[RAYS];
	int			vertical_hit[RAYS];
	bool		facing_down[RAYS];
	bool		facing_up[RAYS];
	bool		facing_left[RAYS];
	bool		facing_right[RAYS];
}				t_rays;

typedef struct s_wall
{
	double		distprojplane;
	double		rect_width;
	double		wall_height;
}				t_wall;

typedef struct s_coords
{
	double		x;
	double		y;
}				t_coords;

typedef struct s_p
{
	double		x;
	double		y;
	double		angle;
	double		move_speed;
	double		rot_speed;
	int			turn_direction;
}				t_p;

typedef struct s_texture
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_texture;

typedef struct s_keys
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			left;
	int			right;
	int			tab;
	int			mouse_x;
	int			old_mouse_x;
}				t_keys;

typedef struct s_map
{
	char		**map;
	int			map_width;
	int			map_height;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
	int			floor_color;
	int			ceiling_color;
}				t_map;

typedef struct s_mini_map
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
}				t_mini_map;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	void		*img;
	t_p			p;
	t_keys		keys;
	t_map		map;
	t_mini_map	mini_map;
	t_rays		rays;
	t_wall		wall;
	t_texture	tx[4];
}				t_mlx;

typedef struct s_pars
{
	char		**rgb;
	char		*hash;
	char		*line;
	int			l;
	int			l1;
	int			fd;
	int			w;
	int			h;
	void		*no;
	void		*so;
	void		*we;
	void		*ea;
	int			f;
	int			c;
	t_mlx		mlx;
}				t_pars;

char			*get_next_line(int fd);
char			*gnl_strjoin(char *s1, char const *s2);
int				first_elem(t_pars *g);
int				second_elem(t_pars *g, char *s, int n);
void			valid_rgb(t_pars *g);
void			check_rgb(t_pars *g, char c);
int				valid_line(t_pars *g);
void			write_error(char *str);
void			loopars(t_pars *g);

//--------------------window.c--------------------

int				mlx_mouse_hide(void);
int				mlx_mouse_move(void *win_ptr, int x, int y);
void			ft_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
void			draw_point(t_mlx *ptr, t_coords coords, int size, int color);
void			draw_line(t_mlx *mlx, int i);
int				wall_check(double new_x, double new_y, char **map);
void			manage_window(t_pars *g);
void			draw_player(t_mlx *ptr, t_coords coords, int size, int color);
void			draw_direc(t_mlx *mlx);
void			draw_ceiling(t_mlx *mlx, t_coords coords);
void			draw_wall(t_mlx *mlx, t_coords coords, int ray_id);
void			draw_floor(t_mlx *mlx, t_coords coords);
void			map_mlx_pixel_put(t_map *map, int x, int y, int color);
void			mini_mlx_pixel_put(t_mini_map *map, int x, int y, int color);
int				close_window(t_mlx *mlx);
int				key_press(int keycode, t_pars *g);
int				key_release(int keycode, t_pars *g);
void			ray_direction(t_rays *rays, int i);
void			corr_steps(t_rays rays, double *xstep, double *ystep, int i);
int				horizontal_inter(t_mlx *mlx, t_coords *hor_inter, int i);
int				vertical_inter(t_mlx *mlx, t_coords *ver_inter, int i);
void			cast_rays(t_mlx *mlx);
void			rays(t_mlx *mlx);
void			render_player(t_mlx *mlx);
void			render_map(t_mlx *mlx);
void			render_mini_map(t_mlx *mlx);
void			find_player_pos(t_p *p, t_map *map);
int				wall_check(double new_x, double new_y, char **map);
int				wall_check_2(double new_x, double new_y, char **map);
void			map_hightnwidth(t_map *map);
int				get_map_color(t_map *map, int x, int y);
void			get_player_ang(t_p *p, char **map);
int				mouse_hook12(int x, int y, t_mlx *mlx);
void			crop_map(t_mlx *mlx);
void			walls(t_mlx *mlx);
void			wall_slide(t_mlx *mlx);
int				check_update(t_mlx *mlx, double new_x, double new_y);
int				get_color(t_mlx *mlx, int x, int y, int tx_id);
#endif
