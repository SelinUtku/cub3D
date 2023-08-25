# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/12 17:03:42 by sutku             #+#    #+#              #
#    Updated: 2023/08/19 15:48:18 by sutku            ###   ########.fr        #                                                               #
# **************************************************************************** #

.SILENT:

CB_SRC		=	main.c texture.c ray_casting.c parsing/parsing.c key_control.c help_functions.c \
				parsing/map_parsing.c parsing/wall_check.c parsing/floor_ceiling.c parsing/wall_textures.c
CB_OBJ		=	$(CB_SRC:.c=.o)


MLX			=	MLX42/build
MLX_LIB		=	MLX42/build/libmlx42.a
GLFW_LIB	=	 -lglfw
#  -L"/opt/homebrew/Cellar/glfw/3.3.8/lib/"
LIBFT		=	libft/
LIBFT_LIB	=	libft/libft.a

CC		= 	cc
RM		=   rm -f
CFLAGS	=	#-Wall -Werror -Wextra

NAME	=	cub3D
# NAME_B	=	so_long_bonus

DEF_COLOR = \033[0;39m
RED = \033[0;91m
GREEN = \033[0;32m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

all:	$(NAME)

$(NAME): $(LIBFT_LIB) $(CB_OBJ) $(MLX_LIB) 
	$(CC) $(CFLAGS) $(LIBFT_LIB) $(CB_OBJ) $(MLX_LIB)  -o $(NAME) $(GLFW_LIB)
	echo "$(GREEN)cub3D compiled successfully$(DEF_COLOR)"

$(MLX_LIB):
	cd MLX42 && cmake -B build && cd ..
	make -C $(MLX)
	echo "$(YELLOW)MLX42 compiled successfully$(DEF_COLOR)"

$(LIBFT_LIB):
	make bonus -C $(LIBFT) && make clean -C $(LIBFT)
	echo "$(GREEN)LIBFT compiled successfully$(DEF_COLOR)"

clean:
	$(RM) $(CB_OBJ)
	$(RM) $(LIBFT_LIB)
	echo "$(MAGENTA)Object-Files are cleaned!$(DEF_COLOR)"

fclean: clean
	$(RM) $(NAME)
	echo "$(MAGENTA)Programs / Libraries are cleaned!$(DEF_COLOR)"

re: fclean all 

.PHONY: all clean fclean re bonus