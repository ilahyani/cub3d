/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 09:02:29 by snouae            #+#    #+#             */
/*   Updated: 2022/11/02 19:04:41 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_map(t_map *map)
{
	int	i;

	i = 0;
	while (map->m[i])
		free(map->m[i++]);
	free(map->m);
}

int	ft_error_malloc(char *message)
{
	if (message)
		printf("%s\n", message);
	exit(1);
}

int	main(int ac, char **av)
{
	t_map	map;

	if (ac != 2 || ft_strcmp(ft_strrchr(av[1], '.'), ".cub"))
		return (printf("Map Does Not Exist. Try again!\n"), 1);
	ft_read(av[1], &map);
	game_init(&map);
	map.textures = (t_texture *) malloc(sizeof(t_texture) * TEXTURES);
	if (!map.textures)
		ft_error_malloc(strerror(ENOMEM));
	if (!ft_check_path(&map))
	{
		ft_free_map(&map);
		return (printf("Map Error. Try again!\n"), 1);
	}
	ft_inti_angl_player(&map);
	draw_map(&map);
	mlx_loop_hook(map.mlx_ptr, deal_key, &map);
	mlx_hook(map.win_ptr, 02, (1L << 0), check_deal_key, &map);
	mlx_hook(map.win_ptr, 03, (1L << 1), keyrealeased, &map);
	mlx_loop(map.mlx_ptr);
	return (clean_up(&map), 0);
}
