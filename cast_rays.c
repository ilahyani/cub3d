/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 19:21:15 by ilahyani          #+#    #+#             */
/*   Updated: 2022/10/31 17:47:43 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
// t_door *add_ray_door(double x, double y, double d)
// {
// 	t_door *dor;
// 	dor = (t_door *)malloc(sizeof(t_door));
// 	dor->x = x;
// 	dor->y = y;
// 	dor->distance = d;
// 	dor->next = NULL;
// 	return (dor);
// }
// void	deletelist(t_door **head)
// {
// 	t_door	*current;
// 	t_door	*next;

// 	current = *head;
// 	while (current)
// 	{
// 		next = current->next;
// 		// free(current->str);
// 		free(current);
// 		current = next;
// 	}
// 	*head = NULL;
// }
int check = 0;
int checkv = 0;
int checkh = 0;
int	cast_rays(t_map *map)
{
	double	rayangle;
	int		rays;
	double	fov;

	fov = 60 * (PI / 180);
	rayangle = map->pa - (fov / 2);
		map->ray = NULL;
	map->ray = (t_dataray *)malloc(sizeof(t_dataray) * WIDTH);
	//map->first = 0;
	rays = -1;
	while (++rays < WIDTH)
	{
		check = 0;
		checkh = 0;
		checkv = 0;
		map->ray[rays].type = WALL;
		castray(map, normalize_angle(rayangle), rays , 1);
		rayangle += fov / WIDTH;
	}
		create_texture_door(map, map->path);
		create_texture(map);
		render3d(map, rays);
		free(map->ray);
		//deletelist(&map->door);
		//map->first = 0;
	// if (map->space > 0)
	// 	jump(map, rays);
	//  else
		
	return (0);
}

float Distance(float x1, float y1, float x2, float y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

t_pos	castray(t_map *map, double rayangle, int i, int flag)
{
	t_pos	h_pos;
	t_pos	v_pos;
	t_pos	pos;

	h_pos = get_horizontal_intersect(map, rayangle, i);
	v_pos = get_vertical_intersect(map, rayangle, i);
	// printf("h_x: %f, h_y: %f\n", h_pos.x, h_pos.y);
	// printf("v_x: %f, v_y: %f\n", v_pos.x, v_pos.y);
	pos = get_shortest_dist(map, h_pos, v_pos);
	if(flag == 1)
	{
		map->ray[i].distance = Distance(map->px, map->py, pos.x, pos.y) * cos(rayangle - map->pa);
		map->ray[i].x = pos.x;
		map->ray[i].y = pos.y;
		map->ray[i].angle = rayangle;
		map->ray[i].tmpx = pos.tmpx;
		map->ray[i].tmpy = pos.tmpy;
		if(check == 1)
			map->ray[i].type = DOOR;
		//map->ray[i].ray  
		
		//map->ray[i].type = WALL;
		// k = floor(pos.y / TILESIZE + map->top);
		// j = floor( pos.x / TILESIZE);
		// if(map->m[k][i] == '1')
		// 	{
		// 		printf("i : %d j : %d\n",(int)pos.y / TILESIZE + map->top , (int)pos.x / TILESIZE);
		// 		printf("i : %f j : %f\n",pos.y / TILESIZE + map->top , pos.x / TILESIZE);
		
		// 		printf("the c is %c\n", map->m[(int)pos.y / TILESIZE + map->top][(int)pos.x / TILESIZE]);
		// 		map->ray[i].type = WALL;
		// 	}
		// // 	{
		// // 		printf("the c is %c\n", map->m[(int)pos.y / TILESIZE + map->top][(int)pos.x / TILESIZE]);
		// // 	}
		// // k = floor(pos.y / TILESIZE + map->top);
		// // j = floor( pos.x / TILESIZE);
		// if(map->m[k][i] == 'D')
		// 	{
		// 		printf("i : %d j : %d\n",(int)pos.y / TILESIZE + map->top , (int)pos.x / TILESIZE);
		// 		printf("i : %f j : %f\n",pos.y / TILESIZE + map->top , pos.x / TILESIZE);
		//  		printf("the c is %c\n", map->m[(int)pos.y / TILESIZE + map->top][(int)pos.x / TILESIZE]);
		//  		map->ray[i].type = DOOR;
				
		// 	}
		if (pos.x == h_pos.x && pos.y == h_pos.y)
		{
			map->ray[i].direction = 'H';
			pos.direction = 'H';
		}
		else
		{
			map->ray[i].direction = 'V';
			pos.direction = 'V';
		}
	}
			if (pos.x == h_pos.x && pos.y == h_pos.y)
				pos.direction = 'H';
			else
				pos.direction = 'V';
	//drawline(map, map->px, map->py , pos.x, pos.y);
	return (pos);
	// printf("x: %f, y: %f\n", pos.x, pos.y);
	//puts("heeeeer");
}


t_pos	get_shortest_dist(t_map *map, t_pos h_pos, t_pos v_pos)
{
	double	v_dist;
	double	h_dist;

	v_dist = sqrt(pow(map->px - v_pos.x, 2) + pow(map->py - v_pos.y, 2));
	h_dist = sqrt(pow(map->px - h_pos.x, 2) + pow(map->py - h_pos.y, 2));
	check = checkv;
	if (v_dist - h_dist >= 0)
	{
		check = checkh;
		return (h_pos);
	}
	return (v_pos);
}

void	set_ray_direction(double rayangle, t_ray *ray)
{
	if (rayangle > 0 && rayangle < PI)
		ray->is_down = 1;
	else
		ray->is_down = 0;
	if (!(ray->is_down))
		ray->is_up = 1;
	else
		ray->is_up = 0;
	if (rayangle < 0.5 * PI || rayangle > 1.5 * PI)
		ray->is_right = 1;
	else
		ray->is_right = 0;
	if (!(ray->is_right))
		ray->is_left = 1;
	else
		ray->is_left = 0;
}

int	find_wall_hit(t_pos *pos, t_ray ray, t_map *map, double rayangle, int i)
{
	(void)rayangle;
	(void)i;
	while (69)
	{
		pos->x = ray.xintercept;
		pos->y = ray.yintercept;
		pos->tmpy = pos->y;
		pos->tmpx = pos->x;
		if (ray.direction == 'H' && ray.is_up)
			pos->tmpy--;
		else if (ray.direction == 'V' && ray.is_left)
			pos->tmpx--;
		//puts("start");
		if (pos->tmpy > (map->rows - 1) * TILESIZE
			|| pos->tmpy < 0
			|| pos->tmpx > map->big_width * TILESIZE
			|| pos->tmpx < 0)
			return (0);
		if( map->m[(int)pos->tmpy  / TILESIZE + map->top]
			[(int)pos->tmpx / TILESIZE] == 'D')
			{
				// printf("tab[%d][%d]\n", (int)pos->tmpy  / TILESIZE + map->top, (int)pos->tmpx / TILESIZE);
				if (ray.direction == 'H')
					checkh = 1;
				else
					checkv = 1;
			}
		if(map->m[(int)pos->tmpy / TILESIZE + map->top]
			[(int)pos->tmpx / TILESIZE] == '1' 
			|| map->m[(int)pos->tmpy / TILESIZE + map->top]
			[(int)pos->tmpx / TILESIZE] == 'D')
			return (0);
		//puts("end");
		ray.xintercept += ray.xstep;
		ray.yintercept += ray.ystep;
	}
	return (0);
}

t_pos	get_vertical_intersect(t_map *map, double rayangle, int i)
{
	t_pos	pos;
	t_ray	ray;

	set_ray_direction(rayangle, &ray);
	ray.xintercept = floor(map->px / TILESIZE) * TILESIZE;
	if (ray.is_right)
		ray.xintercept += TILESIZE;
	ray.yintercept = map->py + (ray.xintercept - map->px) * tan(rayangle);
	ray.xstep = TILESIZE;
	if (ray.is_left)
		ray.xstep *= -1;
	ray.ystep = TILESIZE * tanf(rayangle);
	if (ray.is_up && ray.ystep > 0)
			ray.ystep *= -1;
	else if (ray.is_down && ray.ystep < 0)
			ray.ystep *= -1;
	ray.direction = 'V';
	find_wall_hit(&pos, ray, map, rayangle, i);
	return (pos);
}

t_pos	get_horizontal_intersect(t_map *map, double rayangle, int i)
{
	t_pos	pos;
	t_ray	ray;

	set_ray_direction(rayangle, &ray);
	ray.yintercept = floor(map->py / TILESIZE) * TILESIZE;
	if (ray.is_down)
		ray.yintercept += TILESIZE;
	ray.xintercept = map->px + (ray.yintercept - map->py) / tan(rayangle);
	ray.ystep = TILESIZE;
	if (ray.is_up)
		ray.ystep *= -1;
	ray.xstep = TILESIZE / tan(rayangle);
	if (ray.is_left && ray.xstep > 0)
			ray.xstep *= -1;
	else if (ray.is_right && ray.xstep < 0)
			ray.xstep *= -1;
	ray.direction = 'H';
	find_wall_hit(&pos, ray, map, rayangle, i);
	return (pos);
}

void	drawline(t_map *map, double x0, double y0, double x1, double y1)
{
	t_dda	dda;
	int		i;

	dda.dx = x1 - x0;
	dda.dy = y1 - y0;
	if (fabs(dda.dx) > fabs(dda.dy))
		dda.step = fabs(dda.dx);
	else
		dda.step = fabs(dda.dy);
	dda.xinc = dda.dx / dda.step;
	dda.yinc = dda.dy / dda.step;
	i = -1;
	while (++i <= dda.step)
	{
		my_mlx_pixel_put(&map->data, x0, y0, 0xFF0000);
		x0 += dda.xinc;
		y0 += dda.yinc;
	}
}

double	normalize_angle(double angle)
{
	if (angle > 2 * PI)
		return (angle - (2 * PI));
	else if (angle < 0)
		return (angle + (2 * PI));
	return (angle);
}
