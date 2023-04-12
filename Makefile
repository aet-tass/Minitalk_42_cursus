# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aet-tass <aet-tass@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/11 18:24:31 by aet-tass          #+#    #+#              #
#    Updated: 2023/04/11 18:25:08 by aet-tass         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = client.c utuls.c
OBJ = ${SRC:.c=.o}

NAME = libftprintf.a

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

AR = ar -rc

CC = cc

%.o:%.c
	${CC} ${CFLAGS} -c $<

all : ${NAME}

${NAME}: ${OBJ}
	${AR} ${NAME} ${OBJ}

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY:		all clean fclean re
