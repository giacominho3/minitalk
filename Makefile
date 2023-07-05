# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gifulvi <gifulvi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/01 15:12:00 by gifulvi           #+#    #+#              #
#    Updated: 2022/09/01 15:25:35 by gifulvi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



CLIENT = client
SERVER = server
BONUS1 = server_bonus
BONUS2 = client_bonus

CFLAGS = -Wall -Wextra -Werror

SRCS =	server.c client.c utils.c
SRCB = ./server_bonus.c ./client_bonus.c ./utils.c

OBJ = $(SRCS:%.c=%.o)
OBJB = $(SRCB:%.c=%.o)

SERVERSRC = server.o utils.o
CLIENTSRC = client.o utils.o
SERVERSRCB = server_bonus.o utils.o
CLIENTSRCB = client_bonus.o utils.o

CC = gcc

RM = rm -rf

all: $(CLIENT) $(SERVER)

$(CLIENT): $(OBJ)
			$(CC) $(CFLAGS) $(CLIENTSRC) -o $(CLIENT)

$(SERVER): $(OBJ)
			$(CC) $(CFLAGS) $(SERVERSRC) -o $(SERVER)

$(BONUS1): $(OBJB)
			$(CC) $(CFLAGS) $(SERVERSRCB) -o $(BONUS1)

$(BONUS2): $(OBJB)
			$(CC) $(CFLAGS) $(CLIENTSRCB) -o $(BONUS2)

$(OBJ): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)

bonus: $(BONUS1) $(BONUS2)

norme:
		@norminette $(SRCS) $(SRCB)

clean:
			$(RM) $(OBJ) $(OBJB)
			@echo "\033[33mMinitalk>> Deleted \".o\" files\033[0m"

fclean:		clean
			$(RM) $(CLIENT) $(SERVER) $(BONUS1) $(BONUS2)
			@echo "\033[33mMinitalk>> Project cleaned\033[0m"

re:			fclean all
			@echo "\033[0;92mMinitalk>> Project cleaned and recompiled\033[0m"

.PHONY: all bonus clean fclean re
