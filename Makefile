# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/11 17:00:16 by opokusyn          #+#    #+#              #
#    Updated: 2018/05/11 17:00:18 by opokusyn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

FLAGS = -Wall -Wextra -Werror

SRCS = main.c lem_in.c rooms.c get_ants.c get_links.c remover.c validation.c \
		additional_functions.c

LIBFT = placeholder

.PHONY = $(LIBFT)

BINS = $(SRCS:.c=.o)
all : $(LIBFT) $(NAME)

$(NAME) : $(BINS)
	gcc $(FLAGS) -o $@ $^ -Ilibft  -Llibft -lft

$(LIBFT):
	@make -C libft/

%.o:%.c
	gcc $(FLAGS) -c -o $@ $< -I includes/ -I libft/ 

clean:
	rm -rf $(BINS) $(BINS_LIB)
	make -C libft/ clean

fclean: clean
	rm -rf $(NAME)
	make -C libft/ fclean

re: fclean all
