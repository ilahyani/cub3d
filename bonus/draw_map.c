/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 15:57:26 by ilahyani          #+#    #+#             */
/*   Updated: 2022/11/06 04:00:56 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*pixel;

	if (x < WIDTH && y < HEIGHT && x > 0 && y > 0)
	{	
		pixel = data->addr
			+ (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *) pixel = color;
	}
}

int	check_deal_key(int key, t_map *map)
{
	if (key == 53)
		destroy_notif(map);
	if (key == W)
		map->key_w = 1;
	if (key == 49)
		map->space = 30;
	else if (key == S)
		map->key_s = 1;
	else if (key == A)
		map->key_a = 1;
	else if (key == D)
		map->key_d = 1;
	else if (key == 124)
		map->key_right = 1;
	else if (key == 123)
		map->key_left = 1;
	return (0);
}

int	keyrealeased(int key, t_map *map)
{
	if (key == W)
		map->key_w = 0;
	else if (key == S)
		map->key_s = 0;
	else if (key == A)
		map->key_a = 0;
	else if (key == D)
		map->key_d = 0;
	else if (key == 124)
		map->key_right = 0;
	else if (key == 123)
		map->key_left = 0;
	return (0);
}

void	ft_inti_angl_player(t_map *map)
{
	if (map->view == 'N')
		map->pa = (3 * PI) / 2;
	else if (map->view == 'S')
		map->pa = (PI) / 2;
	else if (map->view == 'W')
		map->pa = PI;
	else if (map->view == 'E')
		map->pa = 0;
	map->pdx = cos(map->pa) * 3;
	map->pdy = sin(map->pa) * 3;
}

void	draw_map(t_map *map)
{
	cast_rays(map);
	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->data.img, 0, 0);
}
