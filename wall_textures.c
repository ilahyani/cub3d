/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:21:57 by ilahyani          #+#    #+#             */
/*   Updated: 2022/10/25 18:18:06 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_texture(t_map *map)
{
	int	i;

	map->textures = (t_texture *) malloc(sizeof(t_texture) * TEXTURES);
	map->textures[0].path = "./texture/bluestone.xpm";
	map->textures[1].path = "./texture/graystone.xpm";
	map->textures[2].path = "./texture/wood.xpm";
	map->textures[3].path = "./texture/redbrick.xpm";
	i = -1;
	while (++i < TEXTURES)
	{
		map->textures[i].img.img = mlx_xpm_file_to_image(map->mlx_ptr,
				map->textures[i].path,
				&map->textures[i].width,
				&map->textures[i].height);
		if (!map->textures[i].img.img)
		{
			printf("Error Reading textures\n GAME CLOSED\n");
			exit(EXIT_FAILURE);
		}
		map->textures[i].img.addr = mlx_get_data_addr(map->textures[i].img.img,
				&map->textures[i].img.bits_per_pixel,
				&map->textures[i].img.line_length,
				&map->textures[i].img.endian);
	}
}

void	apply_texture(t_map *map, double x, double y, int index, double wallheight)
{
	double		offsetx;
	double		offsety;
	int			*buffer;
	int			color;
	t_texture	tex;

	if (map->ray[index].angle >= 0 && map->ray[index].angle <= M_PI && map->ray[index].direction == 'H')
		tex = map->textures[0];
	else if ((map->ray[index].angle < M_PI / 2 || map->ray[index].angle > 3 * M_PI / 2) && map->ray[index].direction == 'V')
		tex = map->textures[1];
	else if ((map->ray[index].angle > M_PI / 2 && map->ray[index].angle < 3 * M_PI / 2) && map->ray[index].direction == 'V')
		tex = map->textures[2];
	else
		tex = map->textures[3];
	buffer = (int *)tex.img.addr;
	if (map->ray[index].direction == 'V')
		offsetx = ((int) map->ray[index].y / TILESIZE);
	else
		offsetx = ((int) map->ray[index].x / TILESIZE);
	offsetx -= floor(offsetx);
	offsetx *= tex.width;
	offsety = (y + (wallheight / 2 - HEIGHT / 2)) * (tex.height / wallheight);
	offsety = floor(offsety);
	offsety *= tex.width;
	color = buffer[(int)offsety + (int)offsetx];

	// double k;
	// k = (tex.height / wallheight);
	// offsety = y + ((wallheight / 2) - (HEIGHT / 2));
	// if (offsety < 0)
	// 	offsety = 0;
	// offsetx = map->ray[index].x;
	// if (map->ray[index].direction == 'V')
	// 	offsetx = map->ray[index].y;
	// offsetx /= TILESIZE;
	// offsetx -= floor(offsetx);
	// offsetx *= map->textures->width;
	// offsety *=  k;
	// offsety = floor(offsety);
	// offsety *= map->textures->width;

	// buffer = (int *)tex.img.addr;
	// color = buffer[(int)offsetx + (int)offsety];
	my_mlx_pixel_put(&map->data, x, y, color);
}
