/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 09:02:29 by snouae            #+#    #+#             */
/*   Updated: 2022/11/01 20:02:34 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_map	map;
	int		i;

	if (ac != 2 || ft_strcmp(ft_strrchr(av[1], '.'), ".cub"))
		return (printf("Map Does Not Exist. Try again!\n"), 1);
	ft_read(av[1], &map);
	game_init(&map);
	i = 0;
	while (map.m[i])
		i++;
	map.leng_map = i;
	i = 0;
	while (map.m[i])
		printf("%s\n", map.m[i++]);
	map.textures = (t_texture *) malloc(sizeof(t_texture) * TEXTURES);
	if (!ft_check_path(&map))
		return (printf("Map Error. Try again!\n"), 1);
	ft_inti_angl_player(&map);
	draw_map(&map);
	mlx_loop_hook(map.mlx_ptr, deal_key, &map);
	mlx_hook(map.win_ptr, 02, (1L << 0), check_deal_key, &map);
	mlx_hook(map.win_ptr, 03, (1L << 1), keyrealeased, &map);
	// mlx_hook(map.win_ptr, 06, (1L << 1), mouse_move, &map);
	mlx_loop(map.mlx_ptr);
	return (clean_up(&map), 0);
}
