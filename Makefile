# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/13 15:58:46 by aviolini          #+#    #+#              #
#    Updated: 2021/04/14 11:41:50 by aviolini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=		cub3D

NAME_BONUS		=		cub3D_bonus

SRCS			=		./files/main.c \
						./files/check_main_args_tools.c \
						./files/get_next_line.c \
						./files/get_next_line_utils.c \
						./files/parsing_params.c \
						./files/parsing_params_tools.c \
						./files/parsing_map.c \
						./files/parsing_map_tools.c \
						./files/key.c \
						./files/player.c \
						./files/image.c \
						./files/image_tools.c \
						./files/image_tools2.c \
						./files/intersections.c \
						./files/sprites.c \
						./files/minimap.c \
						./files/minimap_tools.c \
						./files/bmp.c

SRCS_BONUS		=		./bonus_files/main.c \
						./bonus_files/check_main_args_tools.c \
						./bonus_files/get_next_line.c \
						./bonus_files/get_next_line_utils.c \
						./bonus_files/parsing_params.c \
						./bonus_files/parsing_params_tools.c \
						./bonus_files/parsing_map.c \
						./bonus_files/parsing_map_tools.c \
						./bonus_files/key.c \
						./bonus_files/player.c \
						./bonus_files/image.c \
						./bonus_files/image_tools.c \
						./bonus_files/image_tools2.c \
						./bonus_files/intersections.c \
						./bonus_files/sprites.c \
						./bonus_files/minimap.c \
						./bonus_files/minimap_tools.c \
						./bonus_files/bmp.c

LIB_MLX			=		./minilibx_mms

LFLAGS			=		 -lmlx -framework OpenGL -framework AppKit

OBJS			=		$(SRCS:.c=.o)

OBJS_BONUS		=		$(SRCS_BONUS:.c=.o)

CC				=		gcc

CFLAGS			=		-Wall -Wextra -Werror

RM				=		rm -f

$(NAME)			:		makelib $(OBJS)
						$(CC) $(CFLAGS) -L$(LIB_MLX) $(LFLAGS) -o $(NAME) $(OBJS)

$(NAME_BONUS)	:		makelib $(OBJS_BONUS)
						$(CC) -L$(LIB_MLX) $(LFLAGS) -o $(NAME_BONUS) $(OBJS_BONUS)

all				:		$(NAME)

bonus			:		$(NAME_BONUS)

run				:		$(NAME)
						./$(NAME) maps/map.cub

runbonus		:		$(NAME_BONUS)
						./$(NAME_BONUS) maps/map.cub

makelib			:
						make -C $(LIB_MLX)
						cp $(LIB_MLX)/libmlx.dylib ./

%.o			:			%.c
					$(CC) $(CFLAGS) -c -I$(LIB_MLX) $< -o $@

clean			:
						$(RM) $(OBJS)
						$(RM) $(OBJS_BONUS)

fclean			:		clean
						$(RM) $(NAME)
						$(RM) $(NAME_BONUS)
						$(RM) libmlx.dylib
						$(RM) screenshot.bmp
						make clean -C $(LIB_MLX)

re				:		fclean all

.PHONY			:		all clean fclean re run makelib
