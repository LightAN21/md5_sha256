# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtsai <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/17 12:19:42 by jtsai             #+#    #+#              #
#    Updated: 2019/03/01 14:15:45 by jtsai            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

FLAGS = -Wall -Wextra -Werror

MAIN = main.c

FILES = ft_printf.c re_atoi.c save_itoa.c deal_int.c \
		save_str.c deal_str.c read_flags.c save_char.c save_itoa_base.c \
		read_specifier.c save_wide_string.c

OFILES = $(FILES:.c=.o)

all: $(NAME)

$(NAME):
	@gcc $(FLAGS) -c $(FILES)
	@ar rc $(NAME) $(OFILES)
	@ranlib $(NAME)
#	gcc -g *.c

clean:
	@/bin/rm -f $(OFILES)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
