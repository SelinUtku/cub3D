# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/12 17:03:42 by sutku             #+#    #+#              #
#    Updated: 2023/08/09 01:32:07 by sutku            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

CB_SRC		=	cub3d.c
CB_OBJ		=	$(CB_SRC:.c=.o)

# BONUS_SRC	=	sl_bonus/so_long.c sl_bonus/error.c sl_bonus/put_image.c\
# 				sl_bonus/map_control.c sl_bonus/create_data.c sl_bonus/map_assets.c\
# 				sl_bonus/directions.c sl_bonus/put_image_two.c
# BONUS_OBJ	=	$(BONUS_SRC:.c=.o)

# GNL_SRC		=	gnl/get_next_line_utils.c gnl/get_next_line.c
# GNL_OBJ		=	$(GNL_SRC:.c=.o)

MLX			=	MLX42/build
MLX_LIB		=	MLX42/build/libmlx42.a

# LIBFT		=	libft/
# LIBFT_LIB	=	libft/libft.a

# PRINTF		=	ftprintf/
# PRINTF_LIB	=	ftprintf/libftprintf.a

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

$(NAME): $(CB_OBJ) $(MLX_LIB) 
	$(CC) $(CFLAGS) $(CB_OBJ) $(MLX_LIB)  -o $(NAME) -lglfw 
	echo "$(GREEN)so_long compiled successfully$(DEF_COLOR)"

# $(NAME_B): $(BONUS_OBJ) $(MLX_LIB) $(LIBFT_LIB) $(PRINTF_LIB) $(GNL_OBJ)
# 	$(CC) $(CFLAGS) $(BONUS_OBJ) $(MLX_LIB) $(LIBFT_LIB) $(PRINTF_LIB) $(GNL_OBJ) -o $(NAME_B) -I MLX42/include -lglfw -L /Users/$(USER)/brew/opt/glfw/lib/
# 	echo "$(GREEN)so_long_bonus compiled successfully$(DEF_COLOR)"

$(MLX_LIB):
	cd MLX42 && cmake -B build && cd ..
	make -C $(MLX)
	echo "$(YELLOW)MLX42 compiled successfully$(DEF_COLOR)"

# $(LIBFT_LIB):
# 	make bonus -C $(LIBFT) && make clean -C $(LIBFT)
# 	echo "$(GREEN)LIBFT compiled successfully$(DEF_COLOR)"

# $(PRINTF_LIB):
# 	make -C $(PRINTF) && make clean -C $(PRINTF)
# 	echo "$(GREEN)Printf compiled successfully$(DEF_COLOR)"

clean:
	$(RM) $(CB_OBJ)
	# $(RM) $(GNL_OBJ)
	# $(RM) $(BONUS_OBJ)
	# $(RM) $(LIBFT_LIB) $(PRINTF_LIB)
	echo "$(MAGENTA)Object-Files are cleaned!$(DEF_COLOR)"

fclean: clean
	$(RM) $(NAME)
	# $(RM) $(NAME_B)
	echo "$(MAGENTA)Programs / Libraries are cleaned!$(DEF_COLOR)"

# bonus: $(NAME_B)

re: fclean all 

.PHONY: all clean fclean re bonus