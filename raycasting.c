/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 21:37:41 by ilahyani          #+#    #+#             */
/*   Updated: 2022/11/06 04:27:44 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cast_rays(t_map *map)
{
	double	rayangle;
	int		rays;
	double	fov;

	fov = 60 * (PI / 180);
	rayangle = map->pa - (fov / 2);
	map->ray = (t_dataray *)malloc(sizeof(t_dataray) * WIDTH + 1);
	if (!map->ray)
		ft_error_malloc(strerror(ENOMEM));
	rays = -1;
	while (++rays < WIDTH)
	{
		map->check_hv = 0;
		map->check_h = 0;
		map->check_v = 0;
		map->ray[rays].type = WALL;
		castray(map, normalize_angle(rayangle), rays, 1);
		rayangle += fov / WIDTH;
	}
	create_texture(map);
	render3d(map, rays);
	return (0);
}

t_pos	castray(t_map *map, double rayangle, int i, int flag)
{
	t_pos	h_pos;
	t_pos	v_pos;
	t_pos	pos;

	h_pos = get_horizontal_intersect(map, rayangle);
	v_pos = get_vertical_intersect(map, rayangle);
	pos = get_shortest_dist(map, h_pos, v_pos);
	if (flag == 1)
	{
		map->ray[i].distance = distance(map->px, map->py, pos.x, pos.y)
			* cos(rayangle - map->pa);
		map->ray[i].x = pos.x;
		map->ray[i].y = pos.y;
		map->ray[i].angle = rayangle;
		map->ray[i].tmpx = pos.tmpx;
		map->ray[i].tmpy = pos.tmpy;
		if (pos.x == h_pos.x && pos.y == h_pos.y)
			map->ray[i].direction = 'H';
		else
			map->ray[i].direction = 'V';
	}
	return (pos);
}

int	find_wall_hit(t_pos *pos, t_ray ray, t_map *map)
{
	while (69)
	{
		set_pos(pos, ray);
		if ((pos->tmpy / TILESIZE) > (map->rows - 1)
			|| pos->tmpy < 0
			|| pos->tmpx > (ft_strlen(map->m[(int)(pos->tmpy / TILESIZE)
					+ map->top]) - 1) * TILESIZE
			|| pos->tmpx < 0)
			return (0);
		if (check_for_wall(map, pos))
			return (0);
		ray.xintercept += ray.xstep;
		ray.yintercept += ray.ystep;
	}
	return (0);
}

t_pos	get_vertical_intersect(t_map *map, double rayangle)
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
	find_wall_hit(&pos, ray, map);
	return (pos);
}

t_pos	get_horizontal_intersect(t_map *map, double rayangle)
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
	find_wall_hit(&pos, ray, map);
	return (pos);
}
