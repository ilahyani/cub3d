/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_door.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:48:54 by snouae            #+#    #+#             */
/*   Updated: 2022/11/01 19:46:45 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_door(t_map *map)
{
	if (map->m[(int)map->ray[WIDTH / 2].tmpy / TILESIZE + map->top]
		[(int)map->ray[WIDTH / 2].tmpx / TILESIZE] != 'D')
		map->path = "./texture/main_door.xpm";
	if ((distance(map->px, map->py,
				map->ray[WIDTH / 2].x, map->ray[WIDTH / 2].y) > 35
			&& map->m[(int)map->ray[WIDTH / 2].tmpy / TILESIZE + map->top]
			[(int)map->ray[WIDTH / 2].tmpx / TILESIZE] == 'D'))
		map->path = "./texture/main_door.xpm";
	if ((distance(map->px, map->py,
				map->ray[WIDTH / 2].x, map->ray[WIDTH / 2].y) < 35
			&& map->m[(int)map->ray[WIDTH / 2].tmpy / TILESIZE + map->top]
			[(int)map->ray[WIDTH / 2].tmpx / TILESIZE] == 'D'))
		map->path = "./texture/open_door.xpm";
	if ((distance(map->px, map->py,
				map->ray[WIDTH / 2].x, map->ray[WIDTH / 2].y) < 25
			&& map->m[(int)map->ray[WIDTH / 2].tmpy / TILESIZE + map->top]
			[(int)map->ray[WIDTH / 2].tmpx / TILESIZE] == 'D'))
		map->path = "./texture/open.xpm";
}
