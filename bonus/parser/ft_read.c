/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:25:10 by snouae            #+#    #+#             */
/*   Updated: 2022/11/04 14:35:23 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_read(char *path, t_map *map)
{
	char	*line;
	int		fd;
	char	*buf;

	buf = NULL;
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		printf("Map Does Not Exist. Try again!\n");
		exit(1);
	}
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == '\n')
		{
			line[0] = ' ';
			line[1] = '\n';
			line[2] = '\0';
		}		
		buf = ft_strjoin(buf, line);
		free(line);
		line = get_next_line(fd);
	}
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
