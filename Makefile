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


SFILES = ft_printf.c libft_funcs.c int_and_u.c hex.c \
 		check_params.c length_analize.c unicode.c octal.c \
		atoi_and_itoa.c chars_handle.c flags_and_stars.c \
		print_ints.c strings_handle.c additional_funcs.c

OFILES = ft_printf.o libft_funcs.o int_and_u.o hex.o \
	check_params.o length_analize.o unicode.o octal.o atoi_and_itoa.o \
	chars_handle.o flags_and_stars.o print_ints.o strings_handle.o \
	additional_funcs.o

all: $(NAME)

$(NAME): $(OFILES)
	ar rc $(NAME) $(OFILES)

clean:
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

$(OFILES): %.o:%.c
	gcc -c -Wall -Wextra -Werror $(SFILES)
