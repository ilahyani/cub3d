/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:30:55 by snouae            #+#    #+#             */
/*   Updated: 2022/11/01 16:26:22 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	fill_path_textures(t_map *map, char *way, int *i, int *j)
{
	char	*path;
	char	*tmp;

	path = NULL;
	tmp = (char *)malloc(sizeof(char) * 2);
	while (map->m[*i][*j])
	{
		tmp[0] = map->m[*i][*j];
		path = ft_strjoin(path, tmp);
		(*j)++;
	}
	path = ft_trim(path, ' ');
	if (open(path, O_RDONLY) == -1)
		return (0);
	if (way[0] == 'N')
		map->textures[3].path = path;
	else if (way[0] == 'S')
		map->textures[0].path = path;
	else if (way[0] == 'E')
		map->textures[1].path = path;
	else if (way[0] == 'W')
		map->textures[2].path = path;
	free(tmp);
	return (1);
}

int	ft_valid_path(t_map *map, char *way, int *i, int *j)
{
	*j += skip_spaces(&map->m[*i][*j]);
	if (!*j && *i > map->top)
		return (0);
	if (!ft_strcmp("F", way) || !ft_strcmp("C", way))
	{
		if (!check_colors(map, way, i, j))
			return (0);
	}
	else
	{
		if (!fill_path_textures(map, way, i, j))
			return (0);
	}
	return (1);
}

int	ft_check_line(t_map *map, int *i, int *j, char *way)
{
	if (map->m[*i][*j] == '1' && !map->flags)
	{
		map->top = *i;
		map->flags = 1;
	}
	if (search_way(map, way, i, j))
	{
		if (!ft_valid_path(map, way, i, j))
			return (0);
		map->counter++;
	}
	else if (!map->top)
	{
		if (!ft_valid_line(map, i, j))
			return (0);
	}
	return (1);
}

int	path_exit(t_map *map, char *way)
{
	int	i;
	int	j;
	int	c_player;

	i = 0;
	j = 0;
	map->flags = 0;
	map->counter = 0;
	c_player = 0;
	while (map->m[i])
	{
		j = 0;
		j = skip_spaces(map->m[i]);
		if (!ft_check_line(map, &i, &j, way))
			return (0);
		if (!ft_handle_map(map, i, &j, &c_player))
			return (0);
		i++;
	}
	if (map->counter != 1)
		return (0);
	map->check = 0;
	return (1);
}

int	ft_check_path(t_map *map)
{
	if (!path_exit(map, "NO"))
		return (0);
	if (!path_exit(map, "SO"))
		return (0);
	if (!path_exit(map, "WE"))
		return (0);
	if (!path_exit(map, "EA"))
		return (0);
	if (!path_exit(map, "F"))
		return (0);
	if (!path_exit(map, "C"))
		return (0);
	return (1);
}
