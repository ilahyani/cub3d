/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:23:05 by snouae            #+#    #+#             */
/*   Updated: 2022/11/01 16:28:19 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_trim(char *s1, char c)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	str = 0;
	i = 0;
	j = ft_strlen(s1);
	while (s1[j - 1] == c && j > 0)
		j--;
	str = (char *)malloc((j + 1) * sizeof(char));
	k = 0;
	if (str)
	{
		while (i < j)
			str[k++] = s1[i++];
		str[k] = '\0';
	}
	free(s1);
	s1 = NULL;
	return (str);
}

int	ft_valid_line(t_map *map, int *i, int *j)
{
	while (map->m[*i][*j] && cherche_symbol(map->m[*i][*j], " \t\n"))
		(*j)++;
	if (map->m[*i][*j])
	{
		if (!search_way(map, "F", i, j) && !search_way(map, "NO", i, j)
			&& !search_way(map, "WE", i, j) && !search_way(map, "EA", i, j)
			&& !search_way(map, "C", i, j) && !search_way(map, "SO", i, j))
			return (0);
	}
	return (1);
}

int	fill_rgb(t_map *map, char *way, int *i, int *j)
{
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * 2);
	tmp[1] = '\0';
	if (map->m[*i][*j] != ',')
	{
		tmp[0] = map->m[*i][*j];
		map->nbr = ft_strjoin(map->nbr, tmp);
	}
	if (map->m[*i][*j] && (map->m[*i][*j] == ','
				|| *j == ft_strlen(map->m[*i]) - 1))
	{
		if (ft_atoi(map->nbr) < 0 || ft_atoi(map->nbr) > 255)
			return (0);
		if (!ft_strcmp("F", way))
			map->f[map->k++] = ft_atoi(map->nbr);
		else if (!ft_strcmp("C", way))
			map->c[map->k++] = ft_atoi(map->nbr);
		free(map->nbr);
		map->nbr = NULL;
		if (map->k > 3)
			return (0);
	}
	free(tmp);
	return (1);
}

int	check_colors(t_map *map, char *way, int *i, int *j)
{
	map->k = 0;
	map->nbr = NULL;
	while (map->m[*i][*j])
	{
		if (!fill_rgb(map, way, i, j))
			return (0);
		(*j)++;
	}
	if (map->k < 3 || map->m[*i][*j - 1] == ',')
		return (0);
	return (1);
}

int	caracter_exit(t_map *map, int i, int *j, int *c_player)
{
	if (map->m[i][*j] == 'N' || map->m[i][*j] == 'S' || map->m[i][*j] == 'E'
			|| map->m[i][*j] == 'W')
	{
		map->view = map->m[i][*j];
		map->px = *j * TILESIZE;
		map->py = (i - map->top) * TILESIZE;
		map->m[i][*j] = '0';
		(*c_player)++;
		if (*c_player > 1)
			return (0);
	}
	if (map->m[i][*j] != 'D' && map->m[i][*j] != '1' && map->m[i][*j] != '0'
			&& map->m[i][*j] != 'N' && map->m[i][*j] != 'S'
			&& map->m[i][*j] != 'E'
			&& map->m[i][*j] != 'W' && map->m[i][*j] != ' ')
		return (0);
	return (1);
}
