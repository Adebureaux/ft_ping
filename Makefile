# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/17 17:01:43 by adeburea          #+#    #+#              #
#    Updated: 2026/02/20 13:34:06 by adeburea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


.PHONY: all clean fclean re

CC		=	gcc
NAME	=	ft_ping
FLAGS	=	-Wall -Wextra -Werror
INC		=	-I./include
OBJ_DIR	=	obj

SRC 	=	src/main.c \
			src/socket.c \
			src/icmp.c \
			src/display.c \
			src/checksum.c \
			src/signal.c \
			src/ping_loop.c \
			src/stats.c


OBJ	=	$(SRC:src/%.c=$(OBJ_DIR)/%.o) -lm

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) $(INC) -c $< -o $@

all: $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all