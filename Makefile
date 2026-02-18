# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/17 17:01:43 by adeburea          #+#    #+#              #
#    Updated: 2026/02/18 12:38:35 by adeburea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


.PHONY: all clean fclean re

CC		=	gcc
NAME	=	ft_ping
FLAGS	=	-Wall -Wextra -Werror
INC		=	-I./include
OBJ_DIR	=	obj

SRC 	=	src/main.c \
			src/checksum.c

OBJ	=	$(SRC:src/%.c=$(OBJ_DIR)/%.o)

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