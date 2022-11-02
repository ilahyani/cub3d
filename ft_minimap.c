/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:19:53 by ilahyani          #+#    #+#             */
/*   Updated: 2022/11/02 15:45:47 by ilahyani         ###   ########.fr       */
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
	x = SIZE_MINIMAP / 2;
	y = (SIZE_MINIMAP + 1) / 2;
	draw_player(map, x, y);
	while (j < SIZE_MINIMAP)
	{
		my_mlx_pixel_put(&map->data, j, SIZE_MINIMAP, 0x000000);
		my_mlx_pixel_put(&map->data, SIZE_MINIMAP, j, 0x000000);
		j++;
	}
	my_mlx_pixel_put(&map->data, j, SIZE_MINIMAP, 0x0000FF);
	dx = ((map->px / TILESIZE) * DIV_CUB - x);
	dy = ((map->py / TILESIZE) * DIV_CUB - y);
	draw_minimap(map, dx, dy);
}

void	draw_cub(t_map *map, int i, int j, int color)
{
	int	i1;
	int	j1;

	i1 = i;
	while (i1 < i + DIV_CUB)
	{
		j1 = j;
		while (j1 < j + DIV_CUB)
		{
			if (j1 < SIZE_MINIMAP && i1 < SIZE_MINIMAP)
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
			if (map->m[i][j] == '1' && (k * DIV_CUB) - dy < SIZE_MINIMAP
				&& (j * DIV_CUB) - dx < SIZE_MINIMAP)
				draw_cub(map, (k * DIV_CUB) - dy, (j * DIV_CUB) - dx, 0x000000);
			else if (map->m[i][j] == 'D' && (k * DIV_CUB) - dy < SIZE_MINIMAP
				&& (j * DIV_CUB) - dx < SIZE_MINIMAP)
				draw_cub(map, (k * DIV_CUB) - dy, (j * DIV_CUB) - dx, 0x5d2906);
		}
		i++;
		k++;
	}
}
