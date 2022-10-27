/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:47:34 by ilahyani          #+#    #+#             */
/*   Updated: 2022/10/26 19:07:13 by snouae           ###   ########.fr       */
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
# include <limits.h>
# include "minilibx/mlx.h"

# define WIDTH 1280
# define HEIGHT 860
# define size_minimap 200
# define JUMP_SPEED 20
# define CUBMAP 5
# define DIV_CUB floor(size_minimap / CUBMAP)
# define PI 3.14159
# define TILESIZE 32
# define WALL_WIDTH 1
# define BUFFER_SIZE 1
# define W 13
# define S 1
# define A 0
# define D 2
#define sizemap 0.25

typedef struct s_dda
{
	double	dx;
	double	dy;
	double	step;
	double	xinc;
	double	yinc;
}	t_dda;

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
}	t_pos;

typedef struct s_ray
{
	double	yintercept;
	double	xintercept;
	double	xstep;
	double	ystep;
	int		is_up;
	int		is_down;
	int		is_right;
	int		is_left;
}	t_ray;

typedef struct s_dataray
{
	double	x;
	double	y;
	double distance;
}	t_dataray;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

//TODO: create a global t_game struct
//TODO: organize map struct
typedef struct s_map
{
	char	**m;
	int		leng_map;
	int		rows;
	int		big_width;
	int		top;
	int		flags;
	int		check;
	int		f[3];
	int		c[3];
	double	px;
	double	py;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*image;
	char	view;
	int		key_w;
	int		key_s;
	int		key_A;
	int		key_D;
	int		space;
	int		key_right;
	int		key_left;
	//float	*ray;
	double	pa;
	t_data	data;
	t_player player;
	t_dataray *ray;
}	t_map;

char	*ft_strrchr(char *s, int c);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
int		ft_strlen(char *s);
char	*get_next_line(int fd);
char	*ft_strdup(char *s);
char	**ft_split(char const *s, char c);
int		ft_atoi(char *str);
void	ft_read(char *path, t_map *map);
int		ft_check_path(t_map *map);
int		ft_handle_map(t_map *map, int i, int *j, int *c_player);
int		skip_lines(t_map *map, int i);
int		search_way(t_map *map, char *way, int *i, int *j);
int		skip_spaces(char *str);
int		cherche_symbol(char c, char *str);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_map(t_map *map);
int		cast_rays(t_map *map);
int		deal_key(t_map *map);
int		keyrealeased(int key, t_map *map);
int		check_deal_key(int key, t_map *map);
int		destroy_notif(void);
t_pos	castray(t_map *map, double rayangle, int i, int flag);
double	normalize_angle(double angle);
t_pos	get_horizontal_intersect(t_map *map, double rayangle);
t_pos	get_vertical_intersect(t_map *map, double rayangle);
t_pos	get_shortest_dist(t_map *map, t_pos h_pos, t_pos v_pos);
void	drawline(t_map *map, double x0, double y0, double x1, double y1);
void	ft_inti_angl_player(t_map *map);
void	draw_cub(t_map *map, int i, int j, int color);
void	render3d(t_map *map, int num_rays);
void	ft_mini_map(t_map *map);
float 	Distance(float x1, float y1, float x2, float y2);
void	jump(t_map *map, int num_rays);

#endif