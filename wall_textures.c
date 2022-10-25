/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:21:57 by ilahyani          #+#    #+#             */
/*   Updated: 2022/10/25 12:16:32 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	apply_texture(t_map *map, double x, double y, int index, double wallheight)
{
	int	*buffer;
	int	offsetx;
	int	offsety;
	int	color;
	
	if (map->ray[index].direction == 'V')
		offsetx = (((int) map->ray[index].y % TILESIZE) * (map->texture.width / TILESIZE));
	else
		offsetx = (((int) map->ray[index].x % TILESIZE) * (map->texture.width / TILESIZE));
	offsety = (y + (wallheight / 2 - HEIGHT / 2)) * (map->texture.height / wallheight);
	buffer = (int *)map->texture.img.addr;
	color = buffer[(offsety * map->texture.width + offsetx)];
	my_mlx_pixel_put(&map->data, x, y, color);
}
