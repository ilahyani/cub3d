/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 15:57:26 by ilahyani          #+#    #+#             */
/*   Updated: 2022/09/25 15:57:48 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*pixel;

	pixel = data->addr
		+ (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(int *) pixel = color;
}

void	draw_map(t_map *map)
{
	map->mlx_ptr = mlx_init();
	map->win_ptr = mlx_new_window(map->mlx_ptr,
			map->big_width * 10, map->rows * 10, "cub3d");
	map->data.img = mlx_new_image(map->win_ptr, map->rows * 20,
			map->big_width * 20);
	map->data.addr = mlx_get_data_addr(map->data.img, &map->data.bits_per_pixel,
			&map->data.line_length, &map->data.endian);
	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->data.img, 0, 0);
	mlx_loop(map->mlx_ptr);
}
