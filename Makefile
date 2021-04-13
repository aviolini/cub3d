# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/13 15:58:46 by aviolini          #+#    #+#              #
#    Updated: 2021/04/13 18:16:59 by aviolini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=		cub3D

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

DIR_SRCS		=		./files/

LIB_MLX			=		./minilibx_mms

LFLAGS			=		 -lmlx -framework OpenGL -framework AppKit

OBJS			=		$(SRCS:.c=.o)

CC				=		gcc

CFLAGS			=		-Wall -Wextra -Werror

RM				=		rm -f

$(NAME)			:		makelib $(OBJS)
						$(CC) -L$(LIB_MLX) $(LFLAGS) -o $(NAME) $(OBJS)

all				:		 $(NAME)

run				:		$(NAME)
						./$(NAME) $(DIR_SRCS)map.cub

makelib			:
						make -C $(LIB_MLX)
						cp $(LIB_MLX)/libmlx.dylib ./


%.o			:			%.c
					$(CC) $(CFLAGS) -c -I$(LIB_MLX) $< -o $@

clean			:
						$(RM) $(OBJS)

fclean			:		clean
						$(RM) $(NAME)
						$(RM) libmlx.dylib
						make clean -C $(LIB_MLX)

re				:		fclean all

.PHONY			:		all clean fclean re run makelib
