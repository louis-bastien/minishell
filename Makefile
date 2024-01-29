# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/06 14:39:27 by agheredi          #+#    #+#              #
#    Updated: 2024/01/29 15:41:50 by lbastien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAGS = -Wall -Werror -Wextra -g #-fsanitize='address,undefined'
SRC = srcs/minishell.c \
	srcs/error/error.c \
	srcs/error/exit.c \
	srcs/error/free.c \
	srcs/lexer/lexer.c \
	srcs/lexer/tokens.c \
	srcs/parser/parser.c \
	srcs/parser/redir.c \
	srcs/utils/is_whitespace.c \
	srcs/utils/ft_strlen.c 

CC = gcc
LIBFT_PATH = libft/
LIBFT_LIB = $(LIBFT_PATH)libft.a
OBJ_DIR = obj
OBJECTS = $(addprefix $(OBJ_DIR)/,$(notdir $(SRC:.c=.o)))
HEADER = includes/minishell.h \
		includes/funct.h \
		includes/lib.h \
		includes/struct.h 

# Colors
GREEN = \033[0;32m
YELLOW = \033[1;33m
RED = \033[0;31m
DEFAULT = \033[0m

all: subsystems $(NAME)

$(OBJ_DIR)/%.o: srcs/%.c $(HEADER) Makefile
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) -c -o $@ $<

subsystems:
	@make -C $(LIBFT_PATH) all

$(NAME): $(OBJECTS)
	@$(CC) $(FLAGS) $(OBJECTS) $(LIBFT_LIB) -o $(NAME)
	@echo -e "$(GREEN)$(NAME) created!$(DEFAULT)"

clean:
	@make -C $(LIBFT_PATH) clean
	@rm -rf $(OBJ_DIR)
	@echo -e "$(YELLOW)object files deleted!$(DEFAULT)"

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	@rm -f $(NAME)
	@echo -e "$(RED)all deleted!$(DEFAULT)"

re: fclean all

.PHONY: all re clean fclean subsystems