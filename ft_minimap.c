
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
			if(j1 < size_minimap && i1 < size_minimap)
				my_mlx_pixel_put(&map->data, j1, i1, color);
			j1++;
		}
		i1++;
	}
}

void	draw_player(t_map *map)
{
	double	x1, x2, x3, y1, y2, y3;

	x1 = size_minimap / 2;
	y1 = size_minimap / 2 - 10;
	x2 = size_minimap / 2 + 10;
	y2 = size_minimap / 2 - 10;
	x3 = size_minimap / 2;
	y3 = size_minimap / 2 + 10;
	drawline(map, x1, y1, x2, y2);
 	drawline(map, x2, y2, x3, y3);
 	drawline(map, x3, y3, x1, y1);
	for(int x = x1; x<=x2; x++) {
    	for(int y = y1; y<=y2; y++) {
     		drawline(map, x3, y3, x, y);
    }
  }
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
	float rx;
	float ry;
	rx = cos(map->pa) * 15 + x;
	ry = sin(map->pa) * 15 + y;
	drawline(map, x, y, rx, ry);
	// draw_player(map);
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
			j++;
		}
		i++;
		i1++;
	}
}