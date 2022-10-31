
#include "cub3d.h"

void	ft_lstadd_back(t_door **lst, t_door *new)
{
	t_door	*list;

	if (!new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	list = *lst;
	while (list->next)
		list = list->next;
	list->next = new;
}

static void    drawe_cub(t_map *map, int i, int j, int color)
{
	int	i1;
	int	j1;
	
	i1 = i;
	while (i1 < i + DIV_CUB)
	{
		j1 = j;
		while (j1 < j + DIV_CUB)
		{
			if(j1 < size_minimap && i1 < size_minimap)
				my_mlx_pixel_put(&map->data, j1, i1, color);
			j1++;
		}
		i1++;
	}
}

void	draw_player(t_map *map)
{
	double		x;
	double		y;
	t_player	p;

	x = size_minimap / 2;
	y = (size_minimap + 1) / 2;
	p.old_x1 = x;
	p.old_y1 = y;
	p.old_x2 = size_minimap / 2 + 5;
	p.old_y2 = size_minimap / 2 - 10;
	p.old_x3 = size_minimap / 2 - 5;
	p.old_y3 = size_minimap / 2 - 10;
	p.x1 = (p.old_x1 - x) * sin(map->pa) + (p.old_y1 - y) * cos(map->pa) + x;
	p.y1 = (x - p.old_x1) * cos(map->pa) + (p.old_y1 - y) * sin(map->pa) + y;
	p.x2 = (p.old_x2 - x) * sin(map->pa) + (p.old_y2 - y) * cos(map->pa) + x;
	p.y2 = (x - p.old_x2) * cos(map->pa) + (p.old_y2 - y) * sin(map->pa) + y;
	p.x3 = (p.old_x3 - x) * sin(map->pa) + (p.old_y3 - y) * cos(map->pa) + x;
	p.y3 = (x - p.old_x3) * cos(map->pa) + (p.old_y3 - y) * sin(map->pa) + y;
	drawline(map, p.x1, p.y1, p.x2, p.y2);
	drawline(map, p.x3, p.y3, p.x2, p.y2);
	drawline(map, p.x3, p.y3, p.x1, p.y1);
}

void    ft_mini_map(t_map *map)
{
	int	i;
	int	j;
	i = size_minimap;
	j = 0;
	float x;
	float y;
	x = size_minimap / 2;
	y = (size_minimap + 1) / 2;
	// float rx;
	// float ry;
	// rx = cos(map->pa) * 15 + x;
	// ry = sin(map->pa) * 15 + y;
	// drawline(map, x, y, rx, ry);
	draw_player(map);
	while (j < size_minimap)
	{
		my_mlx_pixel_put(&map->data,j, i, 0x000000);
		my_mlx_pixel_put(&map->data,i, j, 0x000000);
		j++;
	}
	my_mlx_pixel_put(&map->data,j, i, 0x0000FF);
	float dx = ((map->px /TILESIZE) * DIV_CUB - x);
	float dy = ((map->py / TILESIZE) * DIV_CUB  - y); 
	 my_mlx_pixel_put(&map->data, x, y ,  0x000000);
	i = map->top;
	j = 0;
	int i1 = 0;
	while (i < map->rows + map->top)
	{
		j = 0;
		while (map->m[i][j])
		{
			if (map->m[i][j] == '1' && (i1 * DIV_CUB ) - dy <  size_minimap && (j * DIV_CUB) - dx < size_minimap)
				drawe_cub(map, (i1 * DIV_CUB ) - dy, (j * DIV_CUB) - dx, 0x000000);
			else if (map->m[i][j] == 'D' && (i1 * DIV_CUB ) - dy <  size_minimap && (j * DIV_CUB) - dx < size_minimap)
				drawe_cub(map, (i1 * DIV_CUB ) - dy, (j * DIV_CUB) - dx, 0x5d2906);
			j++;
		}
		i++;
		i1++;
	}
}