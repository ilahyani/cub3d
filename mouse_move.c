/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:38:32 by ilahyani          #+#    #+#             */
/*   Updated: 2022/11/02 18:25:37 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_move(int x, int y, void *param)
{
	t_map	*map;

	map = param;
	if (y >= 0 && y <= HEIGHT)
	{
		if (x < WIDTH / 2)
		{
			map->pa -= 0.05;
			if (map->pa < 0)
				map->pa += 2 * PI;
		}
		if (x >= WIDTH / 2)
		{
			map->pa += 0.05;
			if (map->pa > 2 * PI)
				map->pa -= 2 * PI;
		}
	}
	mlx_mouse_move(map->win_ptr, WIDTH / 2, HEIGHT / 2);
	return (0);
}
