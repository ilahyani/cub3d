/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:54:19 by ilahyani          #+#    #+#             */
/*   Updated: 2022/11/04 01:55:36 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render3d(t_map *map, int num_rays)
{
	int		i;
	double	y;
	double	h;
	double	distanceprojectplane;

	i = 0;
	while (i < num_rays)
	{
		if (map->ray[i].distance == 0)
			map->ray[i].distance = 0.000001;
		distanceprojectplane = ((WIDTH) / 2) / fabs(tan(M_PI / 6));
		h = (TILESIZE / map->ray[i].distance) * distanceprojectplane;
		if (h > HEIGHT)
			h = HEIGHT;
		y = ((HEIGHT / 2) - (h / 2));
		render_ceiling(map, i, y);
		render_wall_door(map, i, h, distanceprojectplane);
		render_floor(map, i, h + y);
		i++;
	}
	ft_mini_map(map);
}

void	render_wall_door(t_map *map, int i, double h, double projectplane)
{
	int		texture_color;
	double	wall_height;
	double	down;
	double	y;

	y = ((HEIGHT / 2) - (h / 2));
	down = h + y;
	while (y < down)
	{
		wall_height = ((double)TILESIZE / map->ray[i].distance) * projectplane;
		if (map->ray[i].type == WALL)
		{
			texture_color = get_texture(map, y, i, wall_height);
			my_mlx_pixel_put(&map->data, i, y, texture_color);
		}
		else if (map->ray[i].type == DOOR)
		{
			texture_color = get_texture_door(map, y, i, wall_height);
			my_mlx_pixel_put(&map->data, i, y, texture_color);
		}
		y++;
	}
}

void	render_ceiling(t_map *map, int x, double y)
{
	while (y > 0)
	{
		my_mlx_pixel_put(&map->data, x, y,
			create_rgb(map->c[0], map->c[1], map->c[2]));
		y--;
	}
}

void	render_floor(t_map *map, int x, double y)
{
	while (y < HEIGHT)
	{
		my_mlx_pixel_put(&map->data, x, y,
			create_rgb(map->f[0], map->f[1], map->f[2]));
		y++;
	}
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}
