/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:30:55 by snouae            #+#    #+#             */
/*   Updated: 2022/11/06 04:56:08 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	fill_path_textures(t_map *map, char *way, int *i, int *j)
{
	char	*path;
	char	*tmp;

	path = NULL;
	tmp = (char *)malloc(sizeof(char) * 2);
	tmp[1] = '\0';
	if (!tmp)
		ft_error_malloc(strerror(ENOMEM));
	while (map->m[*i][*j])
	{
		tmp[0] = map->m[*i][(*j)++];
		path = ft_strjoin(path, tmp);
	}
	path = ft_trim(path, ' ');
	free(tmp);
	if (open(path, O_RDONLY) == -1)
		return (0);
	fill_directions(map, way, path);
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

	i = 0;
	j = 0;
	map->flags = 0;
	map->counter = 0;
	map->c_player = 0;
	while (map->m[i])
	{
		j = 0;
		j = skip_spaces(map->m[i]);
		if (!ft_check_line(map, &i, &j, way))
			return (0);
		if (!ft_handle_map(map, i, &j))
			return (0);
		i++;
	}
	if (map->counter != 1 || (!map->check_c && !map->c_player))
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
