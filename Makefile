# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/21 12:14:25 by cchameyr          #+#    #+#              #
#    Updated: 2017/08/02 13:57:57 by cchameyr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

FILES =				

SRCS =				$(addprefix srcs/, $(FILES))

OBJS =				$(addprefix objs/, $(FILES:.c=.o))

CC =				gcc

NAME =				libft_malloc_$(HOSTTYPE).so


LIBFT =				libft/libft.a

FSNAITIZE =			-g3 -fsanitize=address

FLAGS =				-Wall -Wextra -Werror #$(FSNAITIZE)

RM =				rm -rf

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) -shared -o $(FLAGS) $(OBJS) $(LIBFT) $(NAME)
	ln -s $(NAME) libft_malloc.so

$(OBJS):
	$(CC) $(FLAGS) -c $(SRCS)
	@make objs_mv

objs_mv:
	@mkdir objs
	@mv $(FILES:.c=.o) ./objs/

objs_rm:
	@$(RM) objs
	@$(RM) $(FILES:.c=.o)

$(LIBFT):
	make -C ./libft/

clean: objs_rm
	make clean -C ./libft/

fclean: clean
	$(RM) $(LIBFT) $(NAME)

re: fclean all

r: objs_rm
	$(RM) $(NAME)
	@make
