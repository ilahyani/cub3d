/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 20:28:41 by snouae            #+#    #+#             */
/*   Updated: 2022/11/06 03:10:11 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_strrchr(char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	if (!s)
		return (NULL);
	while (i >= 0)
	{
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
	return (s1[i] - s2[i]);
}

char	*ft_strdup(char *s)
{
	char	*new;
	int		leng;
	int		i;

	leng = ft_strlen(s);
	i = 0;
	new = (char *)malloc(sizeof(char) * (leng + 1));
	if (!new)
		return (NULL);
	while (s[i])
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

int	skip(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i] <= 32)
		i++;
	return (i);
}

int	ft_atoi(char *str)
{
	int	i;
	int	s;

	s = 0;
	i = skip(str);
	if (i == -1)
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			s = s * 10 + str[i] - '0';
		else if ((str[i] <= 32))
		{
			while (str[i] && (str[i] <= 32))
				i++;
			if (str[i] == '\0')
				return (s);
			return (-1);
		}
		else if (!(str[i] <= 32))
			return (-1);
		i++;
	}
	return (s);
}
