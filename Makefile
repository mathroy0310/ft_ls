# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maroy <maroy@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/21 00:58:21 by maroy             #+#    #+#              #
#    Updated: 2024/09/10 23:15:26 by maroy            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

LIBFT = libft/libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -Iinclude -Ilibft/inc -g3 -fsanitize=address -Wno-unused-function

LDFLAGS = -Llibft -lft -fsanitize=address

SRC_DIR = src/
OBJ_DIR = obj/
FILES = main/main main/utils main/sort main/stats parsing/errors parsing/options parsing/parsing exec/ls exec/utils display/display display/utils

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

fclean: clean
	@rm -rf $(NAME)