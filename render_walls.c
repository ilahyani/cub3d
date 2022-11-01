/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:54:19 by ilahyani          #+#    #+#             */
/*   Updated: 2022/11/01 20:13:56 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void render3d(t_map *map, int num_rays)
{
    int i;
    int		texture_color;\
    i = 0;
    while(i < num_rays)
    {
        double  distance = map->ray[i].distance;
       if(!distance)
            distance = 0.000001;     
        double  distanceprojectplane =  ((WIDTH) / 2) / fabs(tan(M_PI / 6));
            double h = ((double)TILESIZE / distance) * distanceprojectplane;
            double real_height = h;
        if(h > HEIGHT)
            h = HEIGHT;
            double i1 = ((HEIGHT / 2) - (h / 2));
            double down = h  + i1;
        double up = i1;
        while (up > 0)
        {
            my_mlx_pixel_put(&map->data, i, up, create_rgb(map->c[0], map->c[1], map->c[2]));
            up--;
        }
            while (i1 < down)
            {
                if(map->ray[i].type == WALL)
                {
                    texture_color = get_texture(map, i1, i, real_height);
                    my_mlx_pixel_put(&map->data, i, i1, texture_color);
                }
                else if(map->ray[i].type == DOOR)
                {
                    texture_color = get_texture_door(map, i1, i, real_height);
                    my_mlx_pixel_put(&map->data, i, i1, texture_color);
                }
                i1++;
            }
        while (down < HEIGHT)
        {
            my_mlx_pixel_put(&map->data, i, down, create_rgb(map->f[0], map->f[1], map->f[2]));
            down++;
        }
        i++;
    }
	ft_mini_map(map);
}


