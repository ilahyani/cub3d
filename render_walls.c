/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:54:19 by ilahyani          #+#    #+#             */
/*   Updated: 2022/10/24 10:16:35 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void render3d(t_map *map, int num_rays)
{
    int		i;
    int		jj;
	double	walltop;

    i = 0;
	jj = 0;
    while(i < num_rays)
    {
		double  distance = map->ray[i].distance;
		// float rayDistance = distance;
		// distance = cos(fov) * rayDistance;
		double  distanceprojectplane =  ((WIDTH) / 2) / fabs(tan(M_PI / 6));
		//printf("the height is %f\n", distanceprojectplane);
		//float h = (TILESIZE / rayDistance) * distanceprojectplane;
		double h = ((double)TILESIZE / distance) * distanceprojectplane;
		if(h > HEIGHT)
			h = HEIGHT;
		double i1 = ((HEIGHT / 2) - (h / 2));
		double down = h  + i1;
		double up = i1;
		walltop = i1;
		while (up > 0)
		{
		my_mlx_pixel_put(&map->data, jj, up, 0x87CEEB);
		up--;
		}
		while (i1 <= down)
		{
			// my_mlx_pixel_put(&map->data, jj, i1, 0x00FFFFFF);
			apply_texture(map, jj, i1, i, walltop);
			i1++;
		}
		while (down < HEIGHT)
		{
			my_mlx_pixel_put(&map->data, jj, down, 0x236F21);
			down++;
		}
		jj += 1;
        i++;
    }
	ft_ix(map);
}

static void    drawe_cub(t_map *map, int i, int j, int color)
{
	int	i1;
	int	t1;
	int	j1;
	int	t2;

	t2 = i * TILESIZE * 0.25;
	t1 = j * TILESIZE * 0.25;
	i1 = 0;
	while (i1 < TILESIZE * 0.25)
	{
		j1 = 0;
		while (j1 < TILESIZE * 0.25)
		{
			my_mlx_pixel_put(&map->data, (j1 + t1), (i1 + t2), color);
			j1++;
		}
		i1++;
	}
}

void    ft_ix(t_map *map)
{
	int	i;
	int	j;
	int	i1;

	i = map->top;
	j = 0;
	i1 = 0;
	while (i < map->rows + map->top)
	{
		j = 0;
		while (map->m[i][j])
		{
			if (map->m[i][j] == '1')
				drawe_cub(map, i1, j, 0x0000FF);
			// else if (map->m[i][j] != ' ')
			// 	drawe_cub(map, i1, j, 0x000000);
			j++;
		}
		i++;
		i1++;
	}
	i = 0;
	while (i < WIDTH)
	{
		drawline(map, map->px * 0.25, map->py * 0.25, map->ray[i].x * 0.25, map->ray[i].y * 0.25);
		i++;
	}
	
	// my_mlx_pixel_put(&map->data, map->px*0.25, map->py*0.25, 0x00FFF);
	// my_mlx_pixel_put(&map->data, map->px*0.25, map->py*0.25 - 1, 0x00FFF);
	// my_mlx_pixel_put(&map->data, map->px*0.25 + 1, map->py*0.25, 0x00FFF);
	// my_mlx_pixel_put(&map->data, map->px*0.25, map->py*0.25 + 1, 0x00FFF);
	// my_mlx_pixel_put(&map->data, map->px*0.25 - 1, map->py*0.25, 0x00FFF);
}
