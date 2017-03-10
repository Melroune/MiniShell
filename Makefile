# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akerkeb <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/12 12:56:46 by akerkeb           #+#    #+#              #
#    Updated: 2015/03/30 01:04:42 by akerkeb          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= ft_minishell1

SRC=sh.c ft_cd_verif.c is_builtins.c unsetenv.c env.c env_setenv.c ft_cd.c \
get_next_line.c

FLAGS= -Wall -Wextra -Werror

OBJ=$(SRC:.c=.o)

INCLUDES= -I libft/includes

LIBFT= -L libft -lft 

all: libft.a $(NAME)

libft.a:
		@$(MAKE) -C ./libft

$(NAME): $(OBJ)
		gcc $(FLAG) $(OBJ) $(INCLUDES) $(LIBFT) -o $(NAME)

%.o: %.c
		gcc $(FLAG) $(INCLUDES) -c $^

clean :
		@make clean -C ./libft
			rm -f $(OBJ)

fclean : clean
		rm -f libft.a
			rm -f $(NAME)

re : fclean all
