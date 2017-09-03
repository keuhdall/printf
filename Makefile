# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmarques <lmarques@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/12 13:55:55 by lmarques          #+#    #+#              #
#*   Updated: 2017/09/03 06:32:40 by lmarques         ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

C = clang

NAME = libftprintf.a

FLAGS = -Wall -Wextra -Werror -O2

HEADER = /libft/libft.h

LIBFILES = $(SRC:.c=.o)

SRC = ft_atoi_addr.c \
	  ft_bzero.c \
	  ft_memchr.c \
	  ft_memcpy.c \
	  ft_memset.c \
	  ft_pow.c \
	  ft_strlen.c \
	  ft_strncmp.c \
	  ft_wcharsize.c \
	  ft_strchr_index.c \
	  ft_wstrlen.c \
	  ft_strdup.c \
	  printf_bonuses.c \
	  printf_number.c \
	  printf_parsing.c \
	  printf_string.c \
	  ft_printf.c

all: $(NAME)

$(NAME):
	@gcc $(FLAGS) -c $(SRC) -I $(HEADER)
	@ar rc $(NAME) $(LIBFILES)
	@ranlib $(NAME)

clean:
	@rm -f $(LIBFILES)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
