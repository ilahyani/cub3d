/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:21:57 by ilahyani          #+#    #+#             */
/*   Updated: 2022/11/02 18:12:49 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_texture_door(t_map *map, double y, int index, double wallheight)
{
	double		offsetx;
	double		offsety;
	int			*buffer;
	int			color;

	if (map->ray[index].direction == 'V')
		offsetx = (map->ray[index].y / (double) TILESIZE);
	else
		offsetx = (map->ray[index].x / (double) TILESIZE);
	offsetx -= (int) offsetx;
	offsetx *= map->door_textures[0].width;
	offsety = (y + (wallheight / 2 - HEIGHT / 2))
		* (map->door_textures[0].height / wallheight);
	offsety = (int) offsety;
	offsety *= map->door_textures[0].width;
	buffer = (int *)map->door_textures[0].img.addr;
	color = buffer[(int)offsety + (int)offsetx];
	return (color);
}

void	create_texture_door(t_map *map, char *path)
{
	int	i;

	map->door_textures = (t_texture *) malloc(sizeof(t_texture) * 1);
	if (!map->door_textures)
		ft_error_malloc(strerror(ENOMEM));
	map->door_textures[0].path = path;
	i = -1;
	while (++i < 1)
	{
		map->door_textures[i].img.img = mlx_xpm_file_to_image(map->mlx_ptr,
				map->door_textures[i].path,
				&map->door_textures[i].width,
				&map->door_textures[i].height);
		if (!map->door_textures[i].img.img)
		{
			printf("Error Reading textures\n GAME CLOSED\n");
			exit(EXIT_FAILURE);
		}
		map->door_textures [i].img.addr = mlx_get_data_addr(
				map->door_textures[i].img.img,
				&map->door_textures[i].img.bits_per_pixel,
				&map->door_textures[i].img.line_length,
				&map->door_textures[i].img.endian);
	}
}
