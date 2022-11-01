
#include "cub3d.h"

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
			if(j1 < SIZE_MINIMAP && i1 < SIZE_MINIMAP)
				my_mlx_pixel_put(&map->data, j1, i1, color);
			j1++;
		}
		i1++;
	}
}

void    ft_mini_map(t_map *map)
{
	int	i;
	int	j;
	i = SIZE_MINIMAP;
	j = 0;
	float x;
	float y;
	float rx;
	float ry;
	x = SIZE_MINIMAP / 2;
	y = (SIZE_MINIMAP + 1) / 2;
	rx = cos(map->pa) * 15 + x;
	ry = sin(map->pa) * 15 + y;
	drawline(map, x, y, rx, ry);
	while (j < SIZE_MINIMAP)
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
			if (map->m[i][j] == '1' && (i1 * DIV_CUB ) - dy <  SIZE_MINIMAP && (j * DIV_CUB) - dx < SIZE_MINIMAP)
				drawe_cub(map, (i1 * DIV_CUB ) - dy, (j * DIV_CUB) - dx, 0x000000);
			else if (map->m[i][j] == 'D' && (i1 * DIV_CUB ) - dy <  SIZE_MINIMAP && (j * DIV_CUB) - dx < SIZE_MINIMAP)
				drawe_cub(map, (i1 * DIV_CUB ) - dy, (j * DIV_CUB) - dx, 0x5d2906);
			j++;
		}
		i++;
		i1++;
	}
}