/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:21:57 by ilahyani          #+#    #+#             */
/*   Updated: 2022/10/31 09:27:45 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static t_texture	choose_texture_door(t_map *map, int ray_id)
// {
// 	if (map->ray[ray_id].angle >= 0
// 		&& map->ray[ray_id].angle <= M_PI
// 		&& map->ray[ray_id].direction == 'H')
// 		return (map->door_textures[0]);
// 	else if ((map->ray[ray_id].angle < M_PI / 2
// 			|| map->ray[ray_id].angle > 3 * M_PI / 2)
// 		&& map->ray[ray_id].direction == 'V')
// 		return (map->door_textures[1]);
// 	else if (map->ray[ray_id].angle > M_PI / 2
// 		&& map->ray[ray_id].angle < 3 * M_PI / 2
// 		&& map->ray[ray_id].direction == 'V')
// 		return (map->door_textures[2]);
// 	else
// 		return (map->door_textures[3]);
// }

int	get_texture_door(t_map *map, double y, int index, double wallheight)
{
	double		offsetx;
	double		offsety;
	int			*buffer;
	int 		color;
	t_texture	tex;

	tex = map->door_textures[0];
	if (map->ray[index].direction == 'V')
		offsetx = (map->ray[index].y / (double) TILESIZE);
	else
		offsetx = (map->ray[index].x / (double) TILESIZE);
	offsetx -= (int) offsetx;
	offsetx *= tex.width;
	offsety = (y + (wallheight / 2 - HEIGHT / 2)) * (tex.height / wallheight);
	offsety = (int) offsety;
	offsety *= tex.width;
	buffer = (int *)tex.img.addr;
	color = buffer[(int)offsety + (int)offsetx];
	return (color);
}

void	create_texture_door(t_map *map, char *path)
{
	int	i;

	map->door_textures = (t_texture *) malloc(sizeof(t_texture) * 1);
	map->door_textures[0].path = path;
    // map->door_textures[1].path = "./texture/Roger.xpm"; //luffy
	// map->door_textures[2].path = "./texture/gear5.xpm";
    // map->door_textures[3].path = "./texture/main_door.xpm";
	// map->door_textures[0].path = "./texture/Roger.xpm";
	// map->textures[2].path = "./texture/gear5.xpm";
	// map->textures[3].path = "./texture/luffy.xpm";
	// // map->textures[1].path = "./texture/colorstone.xpm";
	// // map->textures[2].path = "./texture/purplestone.xpm";
	// // map->textures[3].path = "./texture/redbrick.xpm";
	// map->textures[0].path = "./texture/bluestone.xpm";
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
		map->door_textures [i].img.addr = mlx_get_data_addr(map->door_textures[i].img.img,
				&map->door_textures[i].img.bits_per_pixel,
				&map->door_textures[i].img.line_length,
				&map->door_textures[i].img.endian);
	}
}
