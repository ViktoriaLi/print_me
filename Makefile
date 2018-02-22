#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/27 15:23:08 by vlikhotk          #+#    #+#              #
#    Updated: 2017/11/02 15:15:21 by vlikhotk         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libftprintf.a

SFILES = libft_funcs.c ft_printf.c types_analize.c hex.c \
 				check_params.c length_analize.c

OFILES = libft_funcs.o ft_printf.o types_analize.o hex.o \
	check_params.o length_analize.o

all: $(NAME)

$(NAME): $(OFILES)
	ar rc $(NAME) $(OFILES)

clean:
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

%.o : %.c
	gcc -Wall -Wextra -Werror -c $<
