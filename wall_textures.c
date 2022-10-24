/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:21:57 by ilahyani          #+#    #+#             */
/*   Updated: 2022/10/24 12:13:21 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	apply_texture(t_map *map, double x, double y, int index, double walltop)
{
	int		distancefromtop;
	double	offsetx;
	double	offsety;
	int		color;

	// texture = create_texture(); //free
	if (map->ray[index].direction == 'V')
		offsetx = (int) map->ray[index].y % TILESIZE;
	else
		offsetx = (int) map->ray[index].x % TILESIZE;
	distancefromtop = y + (walltop / 2) - (HEIGHT / 2);
	offsety = distancefromtop * (double) TILESIZE;
	color = map->texture.img.addr[(int)(map->texture.img_width * offsety + offsetx)];
	my_mlx_pixel_put(&map->data, x, y, color);
}

int	*create_texture(void)
{
	int	*texture;
	int	x;
	int	y;

	texture = (int *) malloc (sizeof(int) * TILESIZE * TILESIZE);
	x = -1;
	while (++x < TILESIZE)
	{
		y = -1;
		while (++y < TILESIZE)
		{
			if (x % 8 == 0 && y % 8 == 0)
				texture[TILESIZE * y + x] = 0xFF000000;
			else
				texture[TILESIZE * y + x] = 0x000000FF;
		}
	}
	return (texture);
}