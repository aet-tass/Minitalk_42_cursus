# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aet-tass <aet-tass@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/11 18:24:31 by aet-tass          #+#    #+#              #
#    Updated: 2023/04/23 19:01:43 by aet-tass         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror

CC = gcc

RM = rm -rf

SRC_CLIENT = client.c utils_fcts.c 

SRC_SERVER = server.c

OBJ_CLIENT = ${SRC_CLIENT:.c=.o}

OBJ_SERVER =  ${SRC_SERVER:.c=.o}

SRC_CLIENT_BONUS = client_bonus.c utls_fcts.c 

SRC_SERVER_BONUS = server_bonus.c

OBJ_CLIENT_BONUS = ${SRC_CLIENT_BONUS:.c=.o}

OBJ_SERVER_BONUS = ${SRC_SERVER_BONUS:.c=.o}

NAME: compile server client 

all : NAME

compile:
		$(MAKE) -C utils

server: $(OBJ_SERVER)
		$(CC) $(CFLAGS) $(OBJ_SERVER)  utils/libftprintf.a -o server

client: $(OBJ_CLIENT)
		$(CC) $(CFLAGS) $(OBJ_CLIENT) utils/libftprintf.a  -o client

bonus: compile server_bonus client_bonus

server_bonus: $(OBJ_SERVER_BONUS)
		$(CC) $(CFLAGS) $(OBJ_SERVER_BONUS) utils/libftprintf.a -o server_bonus

client_bonus: $(OBJ_CLIENT_BONUS)
		$(CC) $(CFLAGS) $(OBJ_CLIENT_BONUS) utils/libftprintf.a  -o client_bonus

clean:
	@$(RM) $(OBJ_CLIENT) $(OBJ_SERVER) $(OBJ_CLIENT_BONUS) $(OBJ_SERVER_BONUS)
	@$(MAKE) clean -C utils
fclean : clean
	@rm -f server server_bonus client client_bonus
	@$(MAKE) fclean -C utils

re : fclean all
.PHONY:		all clean fclean re
