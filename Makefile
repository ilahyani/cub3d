# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snouae <snouae@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/29 17:52:47 by snouae            #+#    #+#              #
#    Updated: 2022/10/29 22:01:56 by snouae           ###   ########.fr        #
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
	draw_map.c\
	cast_rays.c\
	render_walls.c\
	ft_minimap.c \
	wall_textures.c\
	mouse_move.c\
	door_texture.c

CC = gcc
FLAGS = -Wall -Wextra -Werror
MLXFLAGS = -framework OpenGL -framework Appkit
RM = rm  -rf

OBJ= $(SRC:.c=.o)

NAME = cub3d

MLX = minilibx/libmlx.a

all : $(NAME)

$(NAME) : $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) $(MLXFLAGS) $(MLX) -o $(NAME)

%.o : %.c cub3d.h
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re : fclean all

.PHONY:all clean fclean re