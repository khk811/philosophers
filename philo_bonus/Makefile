# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyunkkim <hyunkkim@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/27 11:57:28 by hyunkkim          #+#    #+#              #
#    Updated: 2022/06/07 11:29:15 by hyunkkim         ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME=philo_bonus
CC=cc
CFLAGS=-Wall -Werror -Wextra
RM=rm -f
SRC=main_bonus.c \
	parse_bonus.c \
	struct_init_bonus.c \
	philo_action_bonus.c \
	time_bonus.c \
	philo_status_bonus.c \
	utils_pid_bonus.c
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
