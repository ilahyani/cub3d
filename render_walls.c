/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:54:19 by ilahyani          #+#    #+#             */
/*   Updated: 2022/10/30 16:43:24 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void jump(t_map *map, int num_rays)
{
    int i;
    int jj = 0;
    static int fact = 0;
    
    mlx_clear_window(map->mlx_ptr, map->win_ptr);
    puts("jumped up");
    i = 0;
    jj = 0;
    while(i < num_rays)
    {
        double  distance = map->ray[i].distance;
        // float rayDistance = distance;
        // distance = cos(fov) * rayDistance;
        double  distanceprojectplane =  ((WIDTH) / 2) / fabs(tan(M_PI / 6));
        //printf("the height is %f\n", distanceprojectplane);
        //float h = (TILESIZE / rayDistance) * distanceprojectplane;
            double h = ((double)TILESIZE / distance) * distanceprojectplane;
        if(h > HEIGHT)
            h = HEIGHT;
        if(fact > 300)
            fact = 300;
        double i1 = ((HEIGHT / 2) - (h / 2)) + fact;
        double down = h  + i1;
        double up = i1;
        while (up > 0)
        {
            my_mlx_pixel_put(&map->data, jj, up, 0x87CEEB);
            up--;
        }
        while (i1 <= down)
        {
            my_mlx_pixel_put(&map->data, jj, i1, 0x00FFFFFF);
            i1++;
        }
        while (down < HEIGHT)
        {
            my_mlx_pixel_put(&map->data, jj, down, 0x236F21);
            down++;
        }
        jj += 1;
        i++;
    }
    mlx_clear_window(map->mlx_ptr, map->win_ptr);
    mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->data.img, 0, 0);
    if (map->space <= 15)
        fact -= JUMP_SPEED;
    else 
        fact += JUMP_SPEED;
    map->space--;
    if (map->space == 0)
        fact = 0;
	ft_mini_map(map);
   
    // while (factor >= 0)
    // {
    //     puts("jumped down");
    //     i = 0;
    //     jj = 0;
    //      while(i < num_rays)
    //     {
    //         double  distance = map->ray[i].distance;
    //         // float rayDistance = distance;
    //         // distance = cos(fov) * rayDistance;
    //         double  distanceprojectplane =  ((WIDTH) / 2) / fabs(tan(M_PI / 6));
    //         //printf("the height is %f\n", distanceprojectplane);
    //         //float h = (TILESIZE / rayDistance) * distanceprojectplane;
    //             double h = ((double)TILESIZE / distance) * distanceprojectplane;
    //         if(h > HEIGHT)
    //             h = HEIGHT;
    //             double i1 = ((HEIGHT / 2) - (h / 2)) - factor;
    //             double down = h  + i1;
    //         double up = i1;
    //         while (up > 0)
    //         {
    //         my_mlx_pixel_put(&map->data, jj, up, 0x87CEEB);
    //         up--;
    //         }
    //         while (i1 <= down)
    //         {
    //             my_mlx_pixel_put(&map->data, jj, i1, 0x00FFFFFF);
    //             i1++;
    //         }
    //         while (down < HEIGHT)
    //         {
    //             my_mlx_pixel_put(&map->data, jj, down, 0x236F21);
    //             down++;
    //         }
    //         jj += 1;
    //         i++;
    //     }
    //     mlx_clear_window(map->mlx_ptr, map->win_ptr);
    //     mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->data.img, 0, 0);
    //     factor--;
    // }
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void render3d(t_map *map, int num_rays)
{
    int i;
    int jj = 0;
    // t_door	*tmp;
    //int tj = 0;

    int		texture_color;
    i = 0;
	    // tmp = map->door;
    while(i < num_rays)
    {
        //printf("the type is %d\n", map->ray[i].type);
        double  distance = map->ray[i].distance;
       if(!distance)
            distance = 0.000001;     
        double  distanceprojectplane =  ((WIDTH) / 2) / fabs(tan(M_PI / 6));
            double h = ((double)TILESIZE / distance) * distanceprojectplane;
            double real_height = h;
        if(h > HEIGHT)
            h = HEIGHT;
            double i1 = ((HEIGHT / 2) - (h / 2));
            double down = h  + i1;
        double up = i1;
        while (up > 0)
        {
            my_mlx_pixel_put(&map->data, jj, up, create_rgb(map->c[0], map->c[1], map->c[2]));
            up--;
        }
            while (i1 < down)
            {
                if(map->ray[i].type == WALL)
                {
                    texture_color = get_texture(map, i1, i, real_height);
                    my_mlx_pixel_put(&map->data, i, i1, texture_color);
                }
                else if(map->ray[i].type == DOOR)
                {
                    texture_color = get_texture_door(map, i1, i, real_height);
                    my_mlx_pixel_put(&map->data, i, i1, texture_color);
                    // texture_color = get_texture(map, i1, i, real_height);
                    // my_mlx_pixel_put(&map->data, i, i1, texture_color);
                }
                i1++;
            }
        while (down < HEIGHT)
        {
            my_mlx_pixel_put(&map->data, jj, down, create_rgb(map->f[0], map->f[1], map->f[2]));
            down++;
        }
        jj += 1;
        i++;
    }
	ft_mini_map(map);
}


