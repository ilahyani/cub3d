/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:54:19 by ilahyani          #+#    #+#             */
/*   Updated: 2022/10/28 18:13:00 by snouae           ###   ########.fr       */
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


void render3d(t_map *map, int num_rays)
{
    int i;
    int jj = 0;
    int		texture_color;
    i = 0;
    while(i < num_rays)
    {
        double  distance = map->ray[i].distance;
        // float rayDistance = distance;
        // distance = cos(fov) * rayDistance;
       /// printf("d :%f\n", distance);
       if(!distance)
            distance = 0.000001;
        
        double  distanceprojectplane =  ((WIDTH) / 2) / fabs(tan(M_PI / 6));
        //printf("the height is %f\n", distanceprojectplane);
        //float h = (TILESIZE / rayDistance) * distanceprojectplane;
            double h = ((double)TILESIZE / distance) * distanceprojectplane;
            //printf("h : %f\n", h);
            double real_height = h;
        if(h > HEIGHT)
            h = HEIGHT;
            double i1 = ((HEIGHT / 2) - (h / 2));
            // if(!i1)
            //     i1 = 50;
            double down = h  + i1;
        double up = i1;
        while (up > 0)
        {
        my_mlx_pixel_put(&map->data, jj, up, 0x87CEEB);
        up--;
        }
            ///printf("the down is %f and the up is %f\n", down, i1);
        while (i1 < down)
        {
           // printf("i1 %f down %f\n", i1, down);
           if(map->ray[i].type == WALL)
           {
                texture_color = get_texture(map, i1, i, real_height);
                my_mlx_pixel_put(&map->data, jj, i1, texture_color);
                //usleep(50000);
           }
           else if (map->ray[i].type == DOOR)
                 my_mlx_pixel_put(&map->data, jj, i1, 0x87EEB);
            i1++;
        }
       // puts("heere");
        while (down < HEIGHT)
        {
            my_mlx_pixel_put(&map->data, jj, down, 0x236F21);
            down++;
        }
        jj += 1;
        i++;
    }
	ft_mini_map(map);
}


