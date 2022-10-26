/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:38:32 by ilahyani          #+#    #+#             */
/*   Updated: 2022/10/26 14:06:52 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define OFFAREA 100

int	mouse_move(int x, int y, void *param)
{
	t_map	*map;

	map = param;
	printf("x: %d | y: %d\n", x, y);
	if (y >= 0 && y <= HEIGHT)
	{
		if (x >= 0 && x <= WIDTH / 2 - OFFAREA)
		{
			map->pa -= 0.01;
			if (map->pa < 0)
				map->pa += 2 * PI;
		}
		if (x > WIDTH / 2 + OFFAREA && x <= WIDTH)
		{
			map->pa += 0.01;
			if (map->pa > 2 * PI)
				map->pa -= 2 * PI;
		}
	}
	return (0);
}