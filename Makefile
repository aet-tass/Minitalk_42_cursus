# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile             ########    ## #     ##    ##             ## ##      #
#                                                     +:+ +:+         +:+      #
#    By: aet-tass <aet-tass@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/11 18:24:31 by aet-tass          #+#    #+#              #
#    Updated: 2023/   ########    ##      # #    ##    ##  ##           ##     #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror

CC = gcc

RM = rm -rf

SRC_CLIENT = client.c utuls.c 

SRC_SERVER = server.c

OBJ_CLIENT = ${SRC_CLIENT:.c=.o}

OBJ_SERVER =  ${SRC_SERVER:.c=.o}

#SRC_CLIENT_BONUS = client_bonus.c utuls.c 

#SRC_SERVER_BONUS = server_bonus.c

#OBJ_CLIENT_BONUS = ${SRC_CLIENT_BONUS:.c=.o}

#OBJ_SERVER_BONUS = ${SRC_SERVER_BONUS:.c=.o}

NAME: server client 

all : NAME

server: $(OBJ_SERVER)
		$(CC) $(CFLAGS) $(OBJ_SERVER)  -o server

client: $(OBJ_CLIENT)
		$(CC) $(CFLAGS) $(OBJ_CLIENT)  -o client

#bonus: server_bonus client_bonus

#server_bonus: $(OBJ_SERVER_BONUS)
	#	$(CC) $(CFLAGS) $(OBJ_SERVER_BONUS) -o server_bonus

#client_bonus: $(OBJ_CLIENT_BONUS)
	#	$(CC) $(CFLAGS) $(OBJ_CLIENT_BONUS)  -o client_bonus

clean:
	@$(RM) $(OBJ_CLIENT) $(OBJ_SERVER) $(OBJ_CLIENT_BONUS) $(OBJ_SERVER_BONUS)
fclean : clean
	@rm -f server server_bonus client client_bonus

re : fclean all
.PHONY:		all clean fclean re


