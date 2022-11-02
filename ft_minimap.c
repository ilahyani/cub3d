/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:19:53 by ilahyani          #+#    #+#             */
/*   Updated: 2022/11/02 18:21:56 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_mini_map(t_map *map)
{
	double	x;
	double	y;
	double	dy;
	double	dx;
	int		j;

	j = 0;
	x = MINIMAP / 2;
	y = (MINIMAP + 1) / 2;
	map->div_cub = floor(MINIMAP / CUBMAP);
	draw_player(map, x, y);
	while (j < MINIMAP)
	{
		my_mlx_pixel_put(&map->data, j, MINIMAP, 0x000000);
		my_mlx_pixel_put(&map->data, MINIMAP, j, 0x000000);
		j++;
	}
	my_mlx_pixel_put(&map->data, j, MINIMAP, 0x0000FF);
	dx = ((map->px / TILESIZE) * map->div_cub - x);
	dy = ((map->py / TILESIZE) * map->div_cub - y);
	draw_minimap(map, dx, dy);
}

void	draw_cub(t_map *map, int i, int j, int color)
{
	int	i1;
	int	j1;

	i1 = i;
	while (i1 < i + map->div_cub)
	{
		j1 = j;
		while (j1 < j + map->div_cub)
		{
			if (j1 < MINIMAP && i1 < MINIMAP)
				my_mlx_pixel_put(&map->data, j1, i1, color);
			j1++;
		}
		i1++;
	}
}

void	draw_player(t_map *map, double x, double y)
{
	t_player	p;

	p.x = cos(map->pa) * 10 + x;
	p.y = sin(map->pa) * 10 + y;
	drawline(map, x, y, p);
	my_mlx_pixel_put(&map->data, x, y, 0x000000);
}

void	draw_minimap(t_map *map, double dx, double dy)
{
	int		i;
	int		j;
	int		k;

	i = map->top;
	j = 0;
	k = 0;
	while (i < map->rows + map->top)
	{
		j = -1;
		while (map->m[i][++j])
		{
			if (map->m[i][j] == '1' && (k * map->div_cub) - dy < MINIMAP
				&& (j * map->div_cub) - dx < MINIMAP)
				draw_cub(map, (k * map->div_cub) - dy,
					(j * map->div_cub) - dx, 0x000000);
			else if (map->m[i][j] == 'D' && (k * map->div_cub) - dy < MINIMAP
				&& (j * map->div_cub) - dx < MINIMAP)
				draw_cub(map, (k * map->div_cub) - dy,
					(j * map->div_cub) - dx, 0x5d2906);
		}
		i++;
		k++;
	}
}
