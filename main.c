/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 09:02:29 by snouae            #+#    #+#             */
/*   Updated: 2022/09/25 15:57:33 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_map	map;
	int		i;

	if (ac != 2 || ft_strcmp(ft_strrchr(av[1], '.'), ".cub"))
	{
		printf("map name is wrong !!");
		return (0);
	}
	ft_read(av[1], &map);
	map.top = 0;
	map.big_width = 0;
	map.check = 0;
	i = 0;
	while (map.m[i])
		i++;
	map.leng_map = i;
	i = 0;
	while (map.m[i])
		printf("%s\n", map.m[i++]);
	if (!ft_check_path(&map))
	{
		printf("The map is incorrect, reconfigure it !!!!!!!!!!!");
		return (1);
	}
	draw_map(&map);
}
