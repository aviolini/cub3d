# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/13 15:58:46 by aviolini          #+#    #+#              #
#    Updated: 2021/04/13 16:48:24 by aviolini         ###   ########.fr        #
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

#OBJS			=		$(DIR_SRCS) $(SRCS:.c=.o)

LIB_MLX			=		./minilibx_mms

LFLAGS			=		 -lmlx -framework OpenGL -framework AppKit

OBJS			=		$(SRCS:.c=.o)

CC				=		gcc

CFLAGS			=		-Wall -Wextra -Werror

RM				=		rm -f

.c.o			:
					$(CC) $(CFLAGS) -c -I$(LIB_MLX) $<

#$(NAME)			:		$(OBJS)
#						-C $(DIR_SRCS)$(CC) -o $(NAME) $(OBJS)

$(NAME)			:		$(OBJS)
						$(CC) -o $(NAME) $(OBJS)

all				:		 $(NAME)

clean			:
						$(RM) $(OBJS)

fclean			:		clean
						$(RM) $(NAME)

re				:		fclean all

.PHONY			:		all clean fclean re
