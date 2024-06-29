# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/28 17:58:43 by bebuber           #+#    #+#              #
#    Updated: 2024/06/28 18:04:42 by bebuber          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = main.c \
		philo.c \
		utils.c \
		threads.c

OBJ = $(SRC:.c=.o)

CC = CC
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lpthread

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re