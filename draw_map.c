/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 15:57:26 by ilahyani          #+#    #+#             */
/*   Updated: 2022/10/31 19:07:36 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <math.h>
double	pdx;
double	pdy;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*pixel;

	if (x < WIDTH && y < HEIGHT && x > 0 && y > 0)
	{	
		pixel = data->addr
			+ (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *) pixel = color;
	}
}

void	draw_cub(t_map *map, int i, int j, int color)
{
	int	i1;
	int	t1;
	int	j1;
	int	t2;

	t2 = i * TILESIZE;
	t1 = j * TILESIZE;
	i1 = 0;
	while (i1 < TILESIZE)
	{
		j1 = 0;
		while (j1 < TILESIZE)
		{
			my_mlx_pixel_put(&map->data, (j1 + t1), (i1 + t2), color);
			j1++;
		}
		i1++;
	}
}

int	destroy_notif(void)
{
	printf("GAME CLOSED\n");
	exit (0);
}

void	ft_pixel(t_map *map)
{
	cast_rays(map);
	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->data.img, 0, 0);
}

int check_deal_key(int key, t_map *map)
{
	if (key == 53)
		destroy_notif();
	if(key == W)
		map->key_w = 1;
	if(key == 49)
		map->space = 30;
	else if(key == S)
		map->key_s = 1;
	else if(key == A)
		map->key_A = 1;
	else if(key == D)
		map->key_D = 1;
	else if(key == 124)
		map->key_right = 1;
	else if (key == 123)
		map->key_left = 1;
	return (0);
}

int keyrealeased(int key, t_map *map)
{
	if(key == W)
		map->key_w = 0;
	else if(key == S)
		map->key_s = 0;
	else if(key == A)
		map->key_A = 0;
	else if(key == D)
		map->key_D = 0;
	else if(key == 124)
		map->key_right = 0;
	else if (key == 123)
		map->key_left = 0;
	return (0);
}

int	deal_key(t_map *map)
{
	//printf("the angal %f\n", map->pa);
	mlx_clear_window(map->mlx_ptr, map->win_ptr);
	//mlx_destroy_image(map->mlx_ptr,  map->data.img);

	static int count = 0;
	if((Distance(map->px, map->py, map->ray[WIDTH / 2].x, map->ray[WIDTH / 2].y) > 35
		&& map->m[(int)map->ray[WIDTH / 2].tmpy / TILESIZE + map->top][(int)map->ray[WIDTH / 2].tmpx / TILESIZE] == 'D'))
		map->path = "./texture/main_door.xpm";
			if((Distance(map->px, map->py, map->ray[WIDTH / 2].x, map->ray[WIDTH / 2].y) < 35
		&& map->m[(int)map->ray[WIDTH / 2].tmpy / TILESIZE + map->top][(int)map->ray[WIDTH / 2].tmpx / TILESIZE] == 'D'))
		map->path = "./texture/open_door.xpm";
	if((Distance(map->px, map->py, map->ray[WIDTH / 2].x, map->ray[WIDTH / 2].y) < 25
		&& map->m[(int)map->ray[WIDTH / 2].tmpy / TILESIZE + map->top][(int)map->ray[WIDTH / 2].tmpx / TILESIZE] == 'D'))
			map->path = "./texture/open.xpm";
	if(map->key_left == 1)
	{
		map->pa -= 0.1;
		if (map->pa < 0)
			map->pa += 2 * PI;
	}
	if(map->key_right == 1)
	{
		map->pa += 0.1;
		if (map->pa > 2 * PI)
			map->pa -= 2 * PI;
	}
	pdx = cos(map->pa) * 3;
	pdy = sin(map->pa) * 3;
	if (map->key_s == 1)
	{
		//int check = 0;
		t_pos pos;
		pos = castray(map, normalize_angle(map->pa + PI), -1 , 0);
		//  printf("x %f and y %f\n", map->px, map->py);
		//  printf("the xray %f and yray %f\n", pos.x , pos.y);
		//  printf("x %f \n", fabs(pos.x - map->px));
		//  printf("y %f \n", fabs(pos.y - map->py));
		// map->py -= pdy;
		// map->px -= pdx;
		// if(map->m[(int)map->py / TILESIZE + map->top] [(int)map->px / TILESIZE] != '0')
		// {
		// 	map->py += pdy;
		// 	map->px += pdx;
		// 	check = 1;
		// }
		// !check && (fabs(pos.x - map->px) <  1 && fabs(pos.y - map->py) < 1)
		//printf("the pos is %c\n", pos.direction);
		if( Distance(map->px, map->py, pos.x, pos.y) > 3)
		{
			map->py -= pdy;
			map->px -= pdx;
		}
		// else if(pos.direction == 'V')
		// {
		// 	puts("here1");
		// 	map->py -= pdy;
		// }
		// else if(pos.direction == 'H')
		// {
		// 		puts("here2");
		// 		map->px -= pdx;
		// }
	}
	if (map->key_w == 1)
	{
		//printf("the first is |%c|\n", map->m[(int)map->py / TILESIZE + map->top - 1][(int)map->px / TILESIZE]);
		// printf("the seconde is |%c|\n", map->m[(int)map->py / TILESIZE + map->top][(int)map->px / TILESIZE + 1]);
		 //printf("the xray %f and yray %f\n", map->ray[HEIGHT / 2].x , map->ray[HEIGHT / 2].y);
		// if(map->m[(int)map->py / TILESIZE + map->top][(int)map->px / TILESIZE] != '0')
		//  	// && map->m[(int)map->py / TILESIZE + map->top][(int)map->px / TILESIZE - 1] == '1'))
		// {
		// 	map->py -= pdy;
		// 	map->px -= pdx;
		// }
		//if(map)
		//printf("x %f and y %f\n", map->px, map->py);
		if( Distance(map->px, map->py, map->ray[WIDTH / 2].x, map->ray[WIDTH / 2].y) > 3)
		{
			map->py += pdy;
			map->px += pdx;
		}
		//printf("%c\n", map->m[(int)(map->ray[WIDTH / 2].tmpy / TILESIZE) + map->top][(int)(map->ray[WIDTH / 2].tmpx / TILESIZE)]);
		if(Distance(map->px, map->py, map->ray[WIDTH / 2].x, map->ray[WIDTH / 2].y) < 5
		  && map->m[(int)(map->ray[WIDTH / 2].tmpy / TILESIZE) + map->top][(int)(map->ray[WIDTH / 2].tmpx / TILESIZE)] == 'D')
		{
			map->m[(int)map->ray[WIDTH / 2].tmpy / TILESIZE + map->top][(int)map->ray[WIDTH / 2].tmpx / TILESIZE] = '0';
			map->dy = (int)map->ray[WIDTH / 2].tmpy / TILESIZE + map->top;
			map->dx = (int)map->ray[WIDTH / 2].tmpx / TILESIZE;
			count++;
		}
		// map->ray[WIDTH / 2].y += 25;
		// map->ray[WIDTH / 2].x += 25;
		// else if(map->ray[WIDTH / 2].direction == 'V')
		// 			map->py += pdy;
		// else if(map->ray[WIDTH / 2].direction == 'H')
		// 			map->px += pdx;
	}
	pdx = cos(map->pa - M_PI_2) * 1;
	pdy = sin(map->pa - M_PI_2) * 1;;
	if (map->key_A == 1)
	{
		map->py += pdy;
		map->px += pdx;
		if(map->m[(int)map->py / TILESIZE + map->top][(int)map->px / TILESIZE] != '0')
		{
			map->py -= pdy;
			map->px -= pdx;
		}
	}
	if (map->key_D == 1)
	{
		map->py -= pdy;
		map->px -= pdx;
		if(map->m[(int)map->py / TILESIZE + map->top][(int)map->px / TILESIZE] != '0')
		{
			map->py += pdy;
			map->px += pdx;
		}
	}
	draw_map(map);
	if(count && (map->key_w == 1 || map->key_s == 1))
		count++;
	if(count == 5)
	{
		count = 0;
		map->path = "./texture/main_door.xpm";
		//if(map->dy != 0 && map->dx != 0)
			map->m[map->dy][map->dx] = 'D';
		map->dx = 0;
		map->dy = 0;
	}
	return (0);
}
void ft_inti_angl_player(t_map *map)
{
	if (map->view == 'N')
		map->pa = (3 * PI) / 2;
	else if (map->view == 'S')
		map->pa = (PI) / 2;
	else if (map->view == 'W')
		map->pa = PI;
	else if (map->view == 'E')
		map->pa = 0;
	pdx = cos(map->pa) * 3;
	pdy = sin(map->pa) * 3;
}

void	draw_map(t_map *map)
{
	ft_pixel(map);
}
