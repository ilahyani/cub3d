/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:47:34 by ilahyani          #+#    #+#             */
/*   Updated: 2022/11/06 04:54:36 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <math.h>
# include <errno.h>
# include <limits.h>
# include "minilibx/mlx.h"

# define WIDTH 1280
# define HEIGHT 860
# define MINIMAP 200
# define JUMP_SPEED 20
# define CUBMAP 15
# define PI 3.14159
# define TILESIZE 16
# define WALL_WIDTH 1
# define BUFFER_SIZE 1
# define W 13
# define S 1
# define A 0
# define D 2
# define TEXTURES 4
# define WALL 1
# define DOOR 0

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_dda
{
	double	dx;
	double	dy;
	double	step;
	double	xinc;
	double	yinc;
}	t_dda;

typedef struct s_texture
{
	t_data	img;
	int		width;
	int		height;
	char	*path;
	char	direction;
}	t_texture;

typedef struct s_player
{
	double	x;
	double	y;
	double	rotation_ang;
}	t_player;

typedef struct s_pos
{
	double	x;
	double	y;
	char	direction;
	double	tmpx;
	double	tmpy;
}	t_pos;

typedef struct s_ray
{
	double	yintercept;
	double	xintercept;
	double	ystep;
	double	xstep;
	char	direction;
	int		is_up;
	int		is_down;
	int		is_right;
	int		is_left;
}	t_ray;

typedef struct s_dataray
{
	double	x;
	double	y;
	double	distance;
	double	angle;
	char	direction;
	int		type;
	double	tmpx;
	double	tmpy;
}	t_dataray;

typedef struct s_door
{
	double			x;
	double			y;
	double			distance;
	char			direction;
	struct s_door	*next;
}	t_door;

typedef struct s_map
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		**m;
	double		px;
	double		py;
	double		pa;
	int			leng_map;
	int			rows;
	int			big_width;
	int			top;
	int			flags;
	int			check;
	int			f[3];
	int			c[3];
	int			key_w;
	int			key_s;
	int			key_a;
	int			key_d;
	int			space;
	int			key_right;
	int			key_left;
	int			first;
	int			counter;
	char		*nbr;
	int			k;
	int			dx;
	int			dy;
	double		pdx;
	double		pdy;
	int			check_h;
	int			check_v;
	int			check_hv;
	char		view;
	int			check_c;
	char		*path;
	int			c_player;
	double		div_cub;
	t_door		*door;
	t_door		*tmp_door;
	t_texture	*textures;
	t_texture	*door_textures;
	t_data		data;
	t_player	player;
	t_dataray	*ray;
}	t_map;

char		*ft_strrchr(char *s, int c);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strchr(char *s, int c);
int			ft_strlen(char *s);
char		*get_next_line(int fd);
char		*ft_strdup(char *s);
char		**ft_split(char const *s, char c);
int			ft_atoi(char *str);
void		ft_read(char *path, t_map *map);
int			ft_check_path(t_map *map);
int			ft_handle_map(t_map *map, int i, int *j);
int			skip_lines(t_map *map, int i);
int			search_way(t_map *map, char *way, int *i, int *j);
int			skip_spaces(char *str);
int			cherche_symbol(char c, char *str);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		draw_map(t_map *map);
int			cast_rays(t_map *map);
int			deal_key(t_map *map);
int			keyrealeased(int key, t_map *map);
int			check_deal_key(int key, t_map *map);
t_pos		castray(t_map *map, double rayangle, int i, int flag);
double		normalize_angle(double angle);
t_pos		get_horizontal_intersect(t_map *map, double rayangle);
t_pos		get_vertical_intersect(t_map *map, double rayangle);
void		set_ray_direction(double rayangle, t_ray *ray);
t_pos		get_shortest_dist(t_map *map, t_pos h_pos, t_pos v_pos);
void		drawline(t_map *map, double x0, double y0, t_player p);
void		ft_inti_angl_player(t_map *map);
void		draw_cub(t_map *map, int i, int j, int color);
void		render3d(t_map *map, int num_rays);
double		distance(double x1, double y1, double x2, double y2);
int			find_wall_hit(t_pos *pos, t_ray ray, t_map *map);
int			get_texture(t_map *map, double y, int index, double wallheight);
void		create_texture(t_map *map);
t_texture	choose_texture(t_map *map, int ray_id);
int			mouse_move(int x, int y, void *param);
void		ft_lstadd_back(t_door **lst, t_door *new);
void		create_texture_door(t_map *map, char *path);
int			get_texture_door(t_map *map, double y,
				int index, double wallheight);
void		set_pos(t_pos *pos, t_ray ray);
int			check_for_wall(t_map *map, t_pos *pos);
void		game_init(t_map *map);
void		clean_up(t_map *map);
char		*ft_trim(char *s1, char c);
int			ft_valid_line(t_map *map, int *i, int *j);
int			check_colors(t_map *map, char *way, int *i, int *j);
int			caracter_exit(t_map *map, int i, int *j);
int			deal_key(t_map *map);
int			destroy_notif(t_map *map);
int			ft_error_malloc(char *message);
void		ft_free_map(t_map *map);
void		render_wall(t_map *map, int i, double h, double projectplane);
void		render_ceiling(t_map *map, int x, double y);
void		render_floor(t_map *map, int x, double y);
int			create_rgb(int r, int g, int b);
void		draw_cub(t_map *map, int i, int j, int color);
void		draw_player(t_map *map, double x, double y);
void		draw_minimap(t_map *map, double dx, double dy);
void		fill_directions(t_map *map, char *way, char *path);

#endif
