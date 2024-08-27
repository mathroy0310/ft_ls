# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maroy <maroy@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/21 00:58:21 by maroy             #+#    #+#              #
#    Updated: 2024/08/27 01:10:27 by maroy            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

LIBFT = libft/libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -g  -Iinclude -Ilibft/inc -fsanitize=address

LDFLAGS = -Llibft -lft

SRC_DIR = src/
OBJ_DIR = obj/
FILES = main/main main/utils main/sort parsing/errors parsing/options parsing/parsing exec/ls exec/utils

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

format:
	clang-format -i $(SRCS) include/*.h

re: clean all

clean:
	@rm -rf $(OBJ_DIR)