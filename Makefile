# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtsai <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/01 14:25:03 by jtsai             #+#    #+#              #
#    Updated: 2019/03/12 12:56:25 by jtsai            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl

FLAGS = -Wall -Wextra -Werror

FILES_0 = ft_ssl.c error_message.c hash_input.c init.c output.c\
		  md5.c md5_functions.c sha256.c sha512.c sha2_32.c sha2_64.c\
		  is_directory.c

FILES_SSL = $(addprefix src_ssl/, $(FILES_0))

O_FILES = $(FILES_0:.c=.o)

LIB = lib/libft/libft.a lib/ft_printf/libftprintf.a

HEADER = -I lib/libft/ -I lib/ft_printf/

all: $(NAME)

$(NAME):
	make -C lib/libft/
	make -C lib/ft_printf/
	gcc -c $(FLAGS) $(HEADER) $(FILES_SSL)
	gcc -o $(NAME) $(O_FILES) $(LIB)

clean:
	make -C lib/libft/ clean
	make -C lib/ft_printf/ clean
	/bin/rm -f $(O_FILES)

fclean: clean
	make -C lib/libft/ fclean
	make -C lib/ft_printf/ fclean
	/bin/rm -f $(NAME)

re: fclean all
