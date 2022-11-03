/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_playr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:38:09 by snouae            #+#    #+#             */
/*   Updated: 2022/11/02 20:44:48 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_move_a_b(t_map *map)
{
	t_pos	pos;

	map->pdx = cos(map->pa - M_PI_2) * 1;
	map->pdy = sin(map->pa - M_PI_2) * 1;
	if (map->key_a == 1)
	{
		pos = castray(map, normalize_angle(map->pa - M_PI_2), -1, 0);
		if (distance(map->px, map->py, pos.x, pos.y) > 3)
		{
			map->py += map->pdy;
			map->px += map->pdx;
		}
	}
	if (map->key_d == 1)
	{
		pos = castray(map, normalize_angle(map->pa + M_PI_2), -1, 0);
		if (distance(map->px, map->py, pos.x, pos.y) > 3)
		{
			map->py -= map->pdy;
			map->px -= map->pdx;
		}
	}
}

void	ft_change_angle(t_map *map)
{
	if (map->key_left == 1)
	{
		map->pa -= 0.1;
		if (map->pa < 0)
			map->pa += 2 * PI;
	}
	if (map->key_right == 1)
	{
		map->pa += 0.1;
		if (map->pa > 2 * PI)
			map->pa -= 2 * PI;
	}
}

int	ft_move_w_s(t_map *map)
{
	t_pos	pos;

	map->pdx = cos(map->pa) * 3;
	map->pdy = sin(map->pa) * 3;
	if (map->key_s == 1)
	{
		pos = castray(map, normalize_angle(map->pa + PI), -1, 0);
		if (distance(map->px, map->py, pos.x, pos.y) > 3)
		{
			map->py -= map->pdy;
			map->px -= map->pdx;
		}
	}
	if (map->key_w == 1)
	{
		if (distance(map->px, map->py,
				map->ray[WIDTH / 2].x, map->ray[WIDTH / 2].y) > 3)
		{
			map->py += map->pdy;
			map->px += map->pdx;
		}
	}
	return (0);
}

int	deal_key(t_map *map)
{
	mlx_clear_window(map->mlx_ptr, map->win_ptr);
	ft_change_angle(map);
	map->pdx = cos(map->pa) * 3;
	map->pdy = sin(map->pa) * 3;
	ft_move_w_s(map);
	ft_move_a_b(map);
	draw_map(map);
	return (0);
}
