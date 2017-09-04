#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: lmarques <lmarques@student.42.fr>          +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2017/09/04 20:47:21 by lmarques          #+#    #+#             *#
#*   Updated: 2017/09/04 21:02:52 by lmarques         ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

NAME = libft.a

SRC = ft_atoi_addr.c \
		ft_bzero.c \
		ft_memchr.c \
		ft_memcpy.c \
		ft_memset.c \
		ft_pow.c \
		ft_strchr_index.c \
		ft_strdup.c \
		ft_strlen.c \
		ft_strncmp.c \
		ft_wcharsize.c \
		ft_wstrlen.c

OBJECTS = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	gcc -Wall -Wextra -Werror -O2 -c $(SRC) -I libft.h
	ar rc $(NAME) $(OBJECTS)
	ranlib $(NAME)

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
