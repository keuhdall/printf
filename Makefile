# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmarques <lmarques@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/12 13:55:55 by lmarques          #+#    #+#              #
#*   Updated: 2017/09/04 22:01:49 by lmarques         ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

HEADER = ./libft/libft.h

SRC = printf_bonuses.c \
	  printf_number.c \
	  printf_parsing.c \
	  printf_string.c \
	  ft_printf.c

OBJECTS = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	make -C libft
	mv libft/libft.a ./$(NAME)
	gcc -Wall -Wextra -Werror -O2 -c $(SRC) -I $(HEADER)
	ar rc $(NAME) $(OBJECTS)
	ranlib $(NAME)

libft/%.o: %.c
	gcc -Wall -Wextra -Werror -O2 -I ./libft/libft.h ./ft_printf.h -o $@ -c $<

clean:
	rm -rf $(OBJECTS)
	make clean -C libft

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
