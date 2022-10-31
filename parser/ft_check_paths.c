/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:30:55 by snouae            #+#    #+#             */
/*   Updated: 2022/10/31 01:09:52 by snouae           ###   ########.fr       */
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
	if (s1 != 0 && c != 0)
	{
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
	}
	free(s1);
	s1 = NULL;
	return (str);
}

int	ft_valid_line(t_map *map, int *i, int *j)
{
	while (map->m[*i][*j] && cherche_symbol(map->m[*i][*j], " \t\n"))
		(*j)++;
	if(map->m[*i][*j])
	{
		if(!search_way(map, "F", i, j) && !search_way(map, "NO", i, j) 
		&& !search_way(map, "WE", i, j) && !search_way(map, "EA", i, j) 
		&& !search_way(map, "C", i, j) && !search_way(map, "SO", i, j))
			return (0);
	}
	return (1);
}

int check_colors(t_map *map, char *way, int *i, int *j)
{
	char	*nbr;
	int		k;
	char *tmp;
	 
	k = 0;
	nbr = NULL;
	tmp = (char *)malloc(sizeof(char) * 2);
	tmp[1] = '\0';
	while (map->m[*i][*j])
	{
		if(map->m[*i][*j] != ',')
		{
			tmp[0] = map->m[*i][*j];
			nbr = ft_strjoin(nbr, tmp);
		}
		if(map->m[*i][*j] && (map->m[*i][*j] == ',' || *j == ft_strlen(map->m[*i]) - 1))
		{
			if(ft_atoi(nbr) < 0 || ft_atoi(nbr) > 255)
				return (0);
			if (!ft_strcmp("F", way))
				map->f[k++] = ft_atoi (nbr);
			else if (!ft_strcmp("C", way))
				map->c[k++] = ft_atoi (nbr);
				free(nbr);
				nbr = NULL;
			if(k > 3)
				return (0);
		}
		(*j)++;
	}
	free(tmp);
	if(k < 3 || map->m[*i][*j - 1] == ',')
		return (0);
	return (1);
}

int	ft_valid_path(t_map *map, char *way, int *i, int *j)
{
	char *path;
	char *tmp;

	path = NULL;
		*j += skip_spaces(&map->m[*i][*j]);
	if(!*j && *i > map->top)
		return (0);
	if(!ft_strcmp("F", way) || !ft_strcmp("C", way))
	{
		if(!check_colors(map, way, i, j))
			return (0);
	}
	else
	{
		tmp = (char *)malloc(sizeof(char) * 2);
		while (map->m[*i][*j])
		{
			tmp[0] = map->m[*i][*j];
			path = ft_strjoin(path, tmp);
			(*j)++;
		}
		path = ft_trim(path,  ' ');
		if(open(path, O_RDONLY) == -1)
			 	return (0);
		if(way[0] == 'N')
			map->textures[3].path = path;
		else if(way[0] == 'S')
			map->textures[0].path = path;
		else if(way[0] == 'E')
			map->textures[1].path = path;
		else if(way[0] == 'W')
			map->textures[2].path = path;
		free(tmp);
	}
	return (1);
}

int path_exit(t_map *map, char *way)
{
	int i;
	int j;
	int c;
	int c_player;

	i = 0;
	j = 0;
	c = 0;
	map->flags = 0;
	c_player = 0;
	while (map->m[i])
	{
		j = 0;
		j =  skip_spaces(map->m[i]);
		if(map->m[i][j] == '1' && !map->flags)
		{
			map->top = i;
			map->flags = 1;
		}
		if (search_way(map, way, &i, &j))
		{
			if(!ft_valid_path(map, way, &i, &j))
				return (0);
			c++; 
		}
		else if (!map->top)
		{
			if(!ft_valid_line(map, &i, &j))
				return (0);
		}
		if(!ft_handle_map(map,i, &j, &c_player))
			return (0);
		i++;
	}
	map->check = 0;
	// printf("the count is %d\n", c_player);
	// if(!map->top && !c_player)
	// 	return (0);
	if(c != 1)
		return (0);
	return (1);
}

int ft_check_path(t_map *map)
{
	if(!path_exit(map, "NO"))
		return (0);
	if(!path_exit(map, "SO"))
		return (0);
	if(!path_exit(map, "WE"))
		return (0);
	if(!path_exit(map, "EA"))
		return (0);
	if(!path_exit(map, "F"))
		return (0);
	if(!path_exit(map, "C"))
		return (0);
	return (1);
}