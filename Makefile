# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/21 12:14:25 by cchameyr          #+#    #+#              #
#    Updated: 2018/03/28 12:05:56 by cchameyr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

FILES =				malloc.c \
					find_memory.c \
					free.c \
					realloc.c \
					print_memory.c \
					print_full_memory.c \
					commons_1.c \
					commons_2.c

SRCS =				$(addprefix srcs/, $(FILES))

OBJS =				$(addprefix objs/, $(FILES:.c=.o))

CC =				gcc

NAME =				libft_malloc_$(HOSTTYPE).so

NAME_FINAL =		libft_malloc.so

FSNAITIZE =			-g3 -fsanitize=address

FLAGS =				#$(FSNAITIZE)#-Wall -Wextra -Werror $(FSNAITIZE)

RM =				rm -rf

all: $(NAME_FINAL)

$(NAME_FINAL): $(OBJS)
	$(CC) -shared $(FLAGS) $(OBJS) -o $(NAME)
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

clean: objs_rm

fclean: clean
	$(RM) $(NAME) $(NAME_FINAL)
	@$(RM) a.out

re: fclean all

r: objs_rm
	$(RM) $(OBJS) $(NAME) $(NAME_FINAL)
	@make
#	gcc main.c
	gcc main.c -L ./ -lft_malloc
#	./a.out
