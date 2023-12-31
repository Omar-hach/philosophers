# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohachami <ohachami@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/19 18:27:21 by ohachami          #+#    #+#              #
#    Updated: 2023/06/19 18:28:10 by ohachami         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc

HEADER = philosophers.h\
	utiles_philo.c\
	actions.c\
	daily_task.c

SRC = philosophers.c\
	utiles_philo.c\
	actions.c\
	daily_task.c

CFLAGS = -Wextra -Werror -Wall #-g -fsanitize=thread

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
