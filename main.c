/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 09:02:29 by snouae            #+#    #+#             */
/*   Updated: 2022/09/25 15:23:14 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}
int zoom = 30;
void draw_map(t_map *map)
{
	map->mlx_ptr = mlx_init();
	map->win_ptr = mlx_new_window(map->mlx_ptr, map->big_width * 10, map->rows * 10, "cub3d");
	//map->data.img = mlx_new_image(map->win_ptr, map->rows * 20, map->big_width * 20);
	//map->data.addr = mlx_get_data_addr(map->data.img, &map->data.bits_per_pixel, &map->data.line_length, &map->data.endian);
	//mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->data.img, 0, 0);
	mlx_loop(map->mlx_ptr);
}

int main(int ac, char **av)
{
    t_map map;
	if (ac != 2 || ft_strcmp(ft_strrchr(av[1], '.'), ".cub"))
	{
		printf("map name is wrong !!");
		return (0);
	}
    ft_read(av[1] ,&map);
	map.top = 0;
	map.big_width = 0;
	map.check = 0;
	int i = 0;
	while(map.m[i])
		i++;
	map.leng_map = i;
	i = 0;
	while (map.m[i])
		printf("%s\n",map.m[i++]);
	if(!ft_check_path(&map))
	{
		printf("The map is incorrect, reconfigure it !!!!!!!!!!!");
		return (1);
	}
	draw_map(&map);
}