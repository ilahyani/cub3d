/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 15:57:26 by ilahyani          #+#    #+#             */
/*   Updated: 2022/09/26 15:17:40 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_cub(t_map *map, int i, int j, int color)
{
	int i1 = i * 32;
	int t1 = i1 + 32;
	while (i1 < t1)
	{
		int j1 = j * 32;
		int t2 = j1 + 32;
		while (j1 < t2)
		{
			my_mlx_pixel_put(&map->data, j1, i1, color);
			j1++;
		}
		i1++;
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*pixel;

	pixel = data->addr
		+ (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(int *) pixel = color;
}

void	draw_map(t_map *map)
{
	int i;
	int j;
	int i1;
	
	map->mlx_ptr = mlx_init();
	map->win_ptr = mlx_new_window(map->mlx_ptr, map->big_width * 32, (map->rows) * 32, "cub3d");
	map->data.img = mlx_new_image(map->mlx_ptr, map->big_width * 32, (map->rows) * 32);
	map->data.addr = mlx_get_data_addr(map->data.img, &map->data.bits_per_pixel, &map->data.line_length, &map->data.endian);
	i = map->top, j = 0, i1 = 0;
	while (i < map->rows + map->top)
	{
		j = 0;
		while (map->m[i][j])
		{
			if(map->m[i][j] == '1')
				draw_cub(map, i1 ,j, 0x00FFFFFF);
			else if (map->m[i][j] == 'N')
				draw_cub(map, i1 ,j, 0x00FFF);
			j++;
		}
		i++;
		i1++;
	}
	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->data.img, 0, 0);
	mlx_loop(map->mlx_ptr);
}
