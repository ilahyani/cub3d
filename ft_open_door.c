/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_door.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:48:54 by snouae            #+#    #+#             */
/*   Updated: 2022/11/02 15:34:07 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_door(t_map *map)
{
	if (map->m[(int)map->ray[WIDTH / 2].tmpy / TILESIZE + map->top]
		[(int)map->ray[WIDTH / 2].tmpx / TILESIZE] != 'D')
		map->path = "./texture/closed.xpm";
	if ((distance(map->px, map->py,
				map->ray[WIDTH / 2].x, map->ray[WIDTH / 2].y) > 35
			&& map->m[(int)map->ray[WIDTH / 2].tmpy / TILESIZE + map->top]
			[(int)map->ray[WIDTH / 2].tmpx / TILESIZE] == 'D'))
		map->path = "./texture/closed.xpm";
	if ((distance(map->px, map->py,
				map->ray[WIDTH / 2].x, map->ray[WIDTH / 2].y) < 35
			&& map->m[(int)map->ray[WIDTH / 2].tmpy / TILESIZE + map->top]
			[(int)map->ray[WIDTH / 2].tmpx / TILESIZE] == 'D'))
		map->path = "./texture/opening.xpm";
	if ((distance(map->px, map->py,
				map->ray[WIDTH / 2].x, map->ray[WIDTH / 2].y) < 25
			&& map->m[(int)map->ray[WIDTH / 2].tmpy / TILESIZE + map->top]
			[(int)map->ray[WIDTH / 2].tmpx / TILESIZE] == 'D'))
		map->path = "./texture/open.xpm";
}
