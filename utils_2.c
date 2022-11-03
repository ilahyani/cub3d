/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 22:27:30 by ilahyani          #+#    #+#             */
/*   Updated: 2022/11/02 19:07:56 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_pos(t_pos *pos, t_ray ray)
{
	pos->x = ray.xintercept;
	pos->y = ray.yintercept;
	pos->tmpy = pos->y;
	pos->tmpx = pos->x;
	if (ray.direction == 'H' && ray.is_up)
		pos->tmpy--;
	else if (ray.direction == 'V' && ray.is_left)
		pos->tmpx--;
}

int	check_for_wall(t_map *map, t_pos *pos)
{
	if (map->m[(int)pos->tmpy / TILESIZE + map->top]
		[(int)pos->tmpx / TILESIZE] == '1'
		|| map->m[(int)pos->tmpy / TILESIZE + map->top]
		[(int)pos->tmpx / TILESIZE] != '0')
		return (1);
	return (0);
}

void	game_init(t_map *map)
{
	int	i;

	i = 0;
	while (map->m[i])
		i++;
	map->leng_map = i;
	map->top = 0;
	map->big_width = 0;
	map->check = 0;
	map->key_w = 0;
	map->key_s = 0;
	map->key_a = 0;
	map->key_d = 0;
	map->key_right = 0;
	map->key_left = 0;
	map->mlx_ptr = mlx_init();
	map->win_ptr = mlx_new_window(map->mlx_ptr, WIDTH, HEIGHT, "cub3d");
	map->data.img = mlx_new_image(map->mlx_ptr, WIDTH, HEIGHT);
	map->data.addr = mlx_get_data_addr(map->data.img,
			&map->data.bits_per_pixel, &map->data.line_length,
			&map->data.endian);
}

void	clean_up(t_map *map)
{
	int	i;

	i = 0;
	while (i < TEXTURES)
		free(map->textures[i++].path);
	free(map->textures);
	ft_free_map(map);
	mlx_destroy_image(map->mlx_ptr, map->data.img);
	mlx_destroy_window(map->mlx_ptr, map->win_ptr);
}

int	destroy_notif(t_map *map)
{
	printf("GAME CLOSED\n");
	clean_up(map);
	exit(0);
}
