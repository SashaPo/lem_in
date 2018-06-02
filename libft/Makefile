# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: opokusyn <opokusyn@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/08 15:39:10 by opokusyn          #+#    #+#              #
#    Updated: 2017/11/16 16:49:27 by opokusyn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
FILES = ft_memcmp.c 		ft_strlcat.c		ft_atoi.c \
		ft_memcpy.c 		ft_strlen.c			ft_bzero.c \
		ft_strncat.c 		ft_memmove.c		ft_strncmp.c \
		ft_isalnum.c		ft_strncpy.c		ft_memdel.c \
		ft_isalpha.c		ft_memset.c			ft_strnstr.c \
		ft_isascii.c		ft_strrchr.c		ft_memalloc.c \
		ft_isdigit.c		ft_strcat.c			ft_strstr.c \
		ft_isprint.c		ft_strchr.c			ft_tolower.c \
		ft_memccpy.c		ft_strcmp.c			ft_toupper.c \
		ft_strcpy.c 		ft_memchr.c			ft_strdup.c \
		ft_putchar.c		ft_putchar_fd.c		ft_putstr.c \
		ft_putstr_fd.c		ft_putendl.c		ft_putendl_fd.c \
		ft_strnew.c			ft_strdel.c			ft_strclr.c \
		ft_striter.c		ft_striteri.c		ft_strmap.c \
		ft_strmapi.c		ft_strequ.c			ft_strnequ.c \
		ft_strsub.c			ft_strjoin.c		ft_strtrim.c \
		ft_putnbr.c			ft_putnbr_fd.c		ft_strsplit.c \
		ft_itoa.c			ft_lstnew.c			ft_lstdelone.c \
		ft_lstdel.c			ft_lstadd.c			ft_lstiter.c \
		ft_lstmap.c			ft_lstpush_b.c		ft_lstclear.c \
		ft_lst_size.c		ft_swap.c			ft_del.c \
		get_next_line.c     ft_itoa_base.c 		ft_itoa_base_2.c    \
		ft_itoa_long.c  ft_itoa_base_long_2.c ft_itoa_ulong.c

PRINTF_SRCS = ft_printf.c ft_init.c ft_unicode.c ft_handle_c.c \
       ft_flag_parser.c ft_specifiers.c ft_bool.c \
       ft_length_parser.c ft_handle_di.c ft_handle_x.c ft_handle_o.c \
       ft_handle_u.c ft_handle_b_for_binary.c ft_handle_p_for_pointer.c \
       ft_handle_percent_and_unknown.c ft_additional_functions.c ft_additional_functions1.c \
       ft_handle_str.c ft_additional_functions2.c ft_additional_functions3.c \
       ft_additional_functions4.c

PRINTFDIR = ft_printf
PRINTF_SOURCES = $(addprefix $(PRINTFDIR)/, $(PRINTF_SRCS))
PRINTF_OBJECTS = $(addprefix $(OBJDIR)/, $(PRINTF_SRCS:.c=.o))

OFILES = $(FILES:%.c=%.o)
OBJDIR = obj
OBJECTS = $(addprefix $(OBJDIR)/, $(OFILES))

FLAGS = -c -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJECTS) $(PRINTF_OBJECTS)
	ar rc $(NAME) $^
	ranlib $(NAME)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	$(CC) $(FLAGS) $< -o $@

$(OBJDIR)/%.o: $(PRINTFDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(FLAGS) $< -o $@ -I .

clean:
	/bin/rm -f $(OFILES)
	rm -rf $(OBJDIR)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
