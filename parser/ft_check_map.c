/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:40:16 by snouae            #+#    #+#             */
/*   Updated: 2022/11/06 20:38:10 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_walls(t_map *map, int i, int *j)
{
	int	k;

	k = i + 1;
	while (map->m[k] && skip_lines(map, k))
		k++;
	if (!map->m[k])
		return (0);
	if (i == map->top || i == map->leng_map - 1
		|| *j == 0 || *j == ft_strlen(map->m[i]) - 1)
		return (0);
	if (map->m[i][*j + 1] == ' ' || map->m[i][*j - 1] == ' '
			|| (map->m[i + 1][*j] && map->m[i + 1][*j] == ' ')
			|| map->m[i - 1][*j] == ' ')
		return (0);
	return (1);
}

int	check_wall_broken(t_map *map, int i, int leng)
{
	int	k;

	if (leng > ft_strlen(map->m[i]))
	{
		k = ft_strlen(map->m[i]);
		while (map->m[i - 1][k])
		{
			if (map->m[i - 1][k] != '1' && map->m[i - 1][k] != ' ')
				return (0);
			k++;
		}
	}
	else if (ft_strlen(map->m[i]) > leng)
	{
		k = leng;
		while (map->m[i][k])
		{
			if (map->m[i][k] != '1' && map->m[i][k] != ' ')
				return (0);
			k++;
		}
	}
	return (1);
}

int	ft_check_map(t_map *map, int i, int *j, int leng)
{
	if (map->m[i][*j] == '1')
		map->rows = (i - map->top) + 1;
	if (!caracter_exit(map, i, j))
		return (0);
	if (map->m[i][*j] == '0')
	{
		if (!check_walls(map, i, j))
			return (0);
	}
	if (!check_wall_broken(map, i, leng))
		return (0);
	if (map->check == 1)
		return (0);
	return (1);
}

int	ft_handle_map(t_map *map, int i, int *j)
{
	int	leng;

	leng = 0;
	if (map->top && i >= map->top)
	{
		if (map->big_width < ft_strlen(map->m[i]))
			map->big_width = ft_strlen(map->m[i]);
		*j = skip_spaces(map->m[i]);
		if (map->m[i][*j] == '\0')
		{
			map->check = 1;
			return (1);
		}
		*j = 0;
		if (i > map->top)
			leng = ft_strlen(map->m[i - 1]);
		while (map->m[i][*j])
		{
			if (!ft_check_map(map, i, j, leng))
				return (0);
			(*j)++;
		}
	}
	return (1);
}
