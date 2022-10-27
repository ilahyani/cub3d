# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/29 17:52:47 by snouae            #+#    #+#              #
#    Updated: 2022/10/27 09:41:26 by ilahyani         ###   ########.fr        #
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
	wall_textures.c\
	mouse_move.c

CC = gcc
FLAGS = -Wall -Wextra -Werror -Ofast #-fsanitize=address
MLXFLAGS = -framework OpenGL -framework Appkit
RM = rm  -rf

OBJ= $(SRC:.c=.o)

NAME = cub3d

LIB = ./minilibx/libmlx.a

all : $(NAME)

$(LIB):
	@make -C minilibx

$(NAME) : $(OBJ) $(LIB)
	@$(CC) $(FLAGS) $(OBJ) $(MLXFLAGS) $(LIB) -o $(NAME)

%.o : %.c cub3d.h
	@$(CC) $(FLAGS) -c $< -o $@

clean_lib:
	@make clean -C minilibx

clean: clean_lib
	$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME) $(LIB)

re: fclean all

.PHONY:all clean fclean re