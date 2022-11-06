# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snouae <snouae@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/29 17:52:47 by snouae            #+#    #+#              #
#    Updated: 2022/11/06 04:02:35 by snouae           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c\
	parser/ft_tools.c\
	parser/get_next_line.c\
	parser/get_next_line_utils.c\
	parser/ft_split.c\
	parser/ft_check_map.c\
	parser/ft_check_paths.c\
	parser/ft_cherch.c\
	parser/ft_read.c\
	parser/ft_check_util.c\
	draw_map.c\
	render_walls.c\
	wall_textures.c\
	ft_move_playr.c\
	raycasting.c\
	utils.c\
	utils_2.c
OBJ= $(SRC:.c=.o)
SRC_BONUS = bonus/main.c\
	bonus/parser/ft_tools.c\
	bonus/parser/get_next_line.c\
	bonus/parser/get_next_line_utils.c\
	bonus/parser/ft_split.c\
	bonus/parser/ft_check_map.c\
	bonus/parser/ft_check_paths.c\
	bonus/parser/ft_cherch.c\
	bonus/parser/ft_read.c\
	bonus/parser/ft_check_util.c\
	bonus/draw_map.c\
	bonus/render_walls.c\
	bonus/ft_minimap.c\
	bonus/wall_textures.c\
	bonus/mouse_move.c\
	bonus/door_texture.c\
	bonus/ft_move_playr.c\
	bonus/ft_open_door.c\
	bonus/raycasting.c\
	bonus/utils.c\
	bonus/utils_2.c
	

OBJ_BONUS= $(SRC_BONUS:.c=.o)
CC = gcc
FLAGS = -Wall -Wextra -Werror -g
MLXFLAGS = -framework OpenGL -framework Appkit
RM = rm  -rf
NAME_BONUS = CUB3D_BONUS
NAME = CUB3D
MLX = minilibx/libmlx.a

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(MLXFLAGS) $(MLX) -o $(NAME)

%.o : %.c cub3d.h bonus/cub3d.h
	$(CC) $(FLAGS) -c $< -o $@

bonus : $(OBJ_BONUS)
	$(CC) $(FLAGS) $(OBJ_BONUS) $(MLXFLAGS) $(MLX) -o $(NAME_BONUS)

clean:
	$(RM) $(OBJ)
	$(RM) $(OBJ_BONUS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME_BONUS)

re : fclean all

.PHONY: all clean fclean re