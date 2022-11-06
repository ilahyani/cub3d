/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:25:10 by snouae            #+#    #+#             */
/*   Updated: 2022/11/06 14:43:03 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	error_file(void)
{
	printf("Map Does Not Exist. Try again!\n");
	exit(1);
}

void	ft_read(char *path, t_map *map)
{
	char	*line;
	int		fd;
	char	*buf;

	buf = NULL;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		error_file();
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == '\n')
		{
			free(line);
			line = ft_strdup(" \n");
		}
		buf = ft_strjoin(buf, line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	map->m = ft_split(buf, '\n');
	free(buf);
	close(fd);
}

char	*ft_trim(char *s1, char c)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	str = 0;
	i = 0;
	j = ft_strlen(s1);
	while (j > 0 && s1[j - 1] == c)
		j--;
	str = (char *)malloc((j + 1) * sizeof(char));
	if (!str)
		ft_error_malloc(strerror(ENOMEM));
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

void	fill_directions(t_map *map, char *way, char *path)
{
	if (way[0] == 'N')
		map->textures[3].path = path;
	else if (way[0] == 'S')
		map->textures[0].path = path;
	else if (way[0] == 'E')
		map->textures[1].path = path;
	else if (way[0] == 'W')
		map->textures[2].path = path;
}
