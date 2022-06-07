# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/17 20:51:27 by hyunkkim          #+#    #+#              #
#    Updated: 2022/06/07 11:00:01 by hyunkkim         ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME=philo
CC=cc
CFLAGS=-Wall -Werror -Wextra
RM=rm -f
SRC=main.c \
	struct_alloc.c \
	struct_init.c \
	philo_status.c \
	philo_action.c \
	parse.c \
	time.c
OBJ=$(SRC:.c=.o)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re :
	$(MAKE) fclean
	$(MAKE) all

.PHONY : all clean fclean re
