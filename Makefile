# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgeorges <mgeorges@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/27 15:07:03 by mgeorges          #+#    #+#              #
#    Updated: 2024/08/30 10:16:51 by mgeorges         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC = gcc

CFLAGS = -Wall -Wextra -Werror -Iheaders/

SOURCE = sources/*.c
GETNEXTLINE = get_next_line/*.c
PRINTF = ft_printf/*.c
LIBRARY = -Lminilibx -lmlx  -lXext -lX11 -lm
MINILIBX = minilibx/

OBJS = $(SOURCE:.c=.o) $(GETNEXTLINE:.c=.o) $(PRINTF:.c=.o)

all:
	make -C $(MINILIBX)
	$(CC) $(CFLAGS) $(SOURCE) $(GETNEXTLINE) $(PRINTF) $(LIBRARY) -o $(NAME)

clean:
		rm -f $(OBJS)
fclean: clean
		make clean -C $(MINILIBX)
		rm -rf $(NAME)

re: fclean all