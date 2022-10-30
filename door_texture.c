/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:21:57 by ilahyani          #+#    #+#             */
/*   Updated: 2022/10/30 14:58:07 by snouae           ###   ########.fr       */
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
	int color = 0;
	t_texture	tex;

	// if (y)
	// {
		// tex = choose_texture_door(map, index);
		 tex = map->door_textures[0];
		if (map->ray[index].direction == 'V')
			offsetx = (map->ray[index].y / (double) TILESIZE);
		else
			offsetx = (map->ray[index].x / (double) TILESIZE);
		offsetx = (map->ray[index].x / (double) TILESIZE);
		offsetx -= (int) offsetx;
		offsetx *= tex.width;
		offsety = (y + (wallheight / 2 - HEIGHT / 2)) * (tex.height / wallheight);
		offsety = (int) offsety;
		offsety *= tex.width;
		buffer = (int *)tex.img.addr;
		// if ((unsigned long)(offsety + offsetx) <= sizeof(buffer) / 4)
		// printf("the offx %f offy %f\n", offsetx, offsety);
		color = buffer[(int)offsety + (int)offsetx];
		//puts("start");
	// }
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