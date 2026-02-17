# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/17 12:49:58 by adeburea          #+#    #+#              #
#    Updated: 2026/02/17 15:55:00 by adeburea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

CC		=	gcc
NAME	=	ft_ping
FLAGS	=	-Wall -Wextra -Werror -g
INC		=	ft_ping.h
OBJ		=	objs
OBJS	=	$(addprefix $(OBJ)/, $(SRCS:.c=.o))
SRCS 	=	main.c \
			parse.c

$(NAME): $(LIBFT) $(OBJ) $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS)

$(OBJ):
	@mkdir -p $(OBJ)

$(OBJ)/%.o: ./%.c
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all