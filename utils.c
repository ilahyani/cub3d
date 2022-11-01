/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 21:41:56 by ilahyani          #+#    #+#             */
/*   Updated: 2022/11/01 19:46:45 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

double	distance(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

t_pos	get_shortest_dist(t_map *map, t_pos h_pos, t_pos v_pos)
{
	double	v_dist;
	double	h_dist;

	v_dist = sqrt(pow(map->px - v_pos.x, 2) + pow(map->py - v_pos.y, 2));
	h_dist = sqrt(pow(map->px - h_pos.x, 2) + pow(map->py - h_pos.y, 2));
	map->check_hv = map->check_v;
	if (v_dist - h_dist >= 0)
	{
		map->check_hv = map->check_h;
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
