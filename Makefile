# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aet-tass <aet-tass@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/11 18:24:31 by aet-tass          #+#    #+#              #
#    Updated: 2023/04/14 05:26:50 by aet-tass         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = server.c utils.c
OBJ = ${SRC:.c=.o}

NAME = server

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

CC = cc

%.o:%.c
	${CC} ${CFLAGS} -c $<

all : ${NAME}

${NAME}: ${OBJ}
	 ${CC} ${CFLAGS} ${OBJ} -o ${NAME}

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY:		all clean fclean re


