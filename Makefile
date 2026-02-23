# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/28 16:04:40 by edi-maio          #+#    #+#              #
#    Updated: 2026/02/11 15:36:11 by edi-maio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CFLAGS = -Wall -Wextra -Werror

C_FILES = utils.c \
		  main.c \
		  monitoring.c \
		  parsing.c \
		  philos.c \
		  display.c

SRCS = $(addprefix srcs/,$(C_FILES))

OBJS = $(SRCS:.c=.o)

.o: .c
	cc $(CFLAGS) -I $(INCLUDES) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	cc $(CFLAGS) $(MLX_FLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
