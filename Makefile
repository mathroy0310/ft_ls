# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maroy <maroy@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/21 00:58:21 by maroy             #+#    #+#              #
#    Updated: 2024/08/21 01:38:12 by maroy            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

LIBFT = libft/libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -Iinclude -Ilibft/inc

LDFLAGS = -Llibft -lft

SRC_DIR = src/
OBJ_DIR = obj/
FILES = main/main parsing/errors parsing/options parsing/parsing

SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

bonus: all

$(NAME): $(LIBFT) $(OBJS)
	@echo "Compiling $(NAME)..."
	@$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)
	@echo "Done !"

$(LIBFT):
	@make -C libft

re: clean all

clean:
	@rm -rf $(OBJ_DIR)
	@make -C libft clean