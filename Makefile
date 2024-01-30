# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/06 14:39:27 by agheredi          #+#    #+#              #
#    Updated: 2024/01/30 17:00:39 by lbastien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

#Executer
CC = gcc
FLAGS = -Wall -Werror -Wextra -g #-fsanitize='address,undefined'

#source files and headers
SRC = srcs/minishell.c \
	srcs/error/error.c \
	srcs/error/exit.c \
	srcs/error/free.c \
	srcs/lexer/lexer.c \
	srcs/lexer/tokens.c \
	srcs/parser/parser.c \
	srcs/parser/redirections.c \
	srcs/utils/is_whitespace.c \
	srcs/utils/ft_strlen.c \
	srcs/utils/ft_init.c \
	srcs/executor/ft_heredoc.c \

HEADER = includes/minishell.h \
		includes/funct.h \
		includes/lib.h \
		includes/struct.h 

#Local libraries
LIBFT_PATH = libft/
LIBFT_LIB = -lft

READLINE_PATH = readline-8.1/
READLINE_LIB = -lreadline -lhistory

LIBS = $(LIBFT_LIB) $(READLINE_LIB) -lncurses
LIB_FLAGS = -L$(LIBFT_PATH) -L$(READLINE_PATH)

READLINE_ABSOLUTE_PATH = $(shell pwd)/readline-8.1

#Objects
OBJ_DIR = obj
OBJECTS = $(addprefix $(OBJ_DIR)/,$(notdir $(SRC:.c=.o)))

INCLUDES =-Iincludes -I$(LIBFT_PATH)

# Colors
GREEN = \033[0;32m
YELLOW = \033[1;33m
RED = \033[0;31m
DEFAULT = \033[0m

all: subsystems $(NAME)

# General rule for files in srcs/
$(OBJ_DIR)/%.o: srcs/%.c $(HEADER) Makefile
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) $(INCLUDES) -c -o $@ $<

# Specific rules for each subdirectory
$(OBJ_DIR)/%.o: srcs/error/%.c $(HEADER) Makefile
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) $(INCLUDES) -c -o $@ $<

$(OBJ_DIR)/%.o: srcs/lexer/%.c $(HEADER) Makefile
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) $(INCLUDES) -c -o $@ $<

$(OBJ_DIR)/%.o: srcs/parser/%.c $(HEADER) Makefile
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) $(INCLUDES) -c -o $@ $<

$(OBJ_DIR)/%.o: srcs/executor/%.c $(HEADER) Makefile
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) $(INCLUDES) -c -o $@ $<

$(OBJ_DIR)/%.o: srcs/utils/%.c $(HEADER) Makefile
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) $(INCLUDES) -c -o $@ $<

subsystems: configure-readline
	@make -C $(LIBFT_PATH) all
	@make -C $(READLINE_PATH) static

configure-readline:
	@if ! grep -q "$(READLINE_ABSOLUTE_PATH)" "$(READLINE_PATH)/config.status"; then \
		echo "$(YELLOW)READLINE WILL BE CONFIGURED$(DEFAULT)"; \
		cd $(READLINE_PATH) && ./configure; \
	else \
	 	echo "$(YELLOW)READLINE ALREADY CONFIGURED$(DEFAULT)"; \
	fi

$(NAME): $(OBJECTS)
	@$(CC) $(FLAGS) $(LIB_FLAGS) $(OBJECTS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)$(NAME) created!$(DEFAULT)"

clean:
	@make -C $(LIBFT_PATH) clean
	@make -C $(READLINE_PATH) clean
	@rm -rf $(OBJ_DIR)
	@echo "$(YELLOW)object files deleted!$(DEFAULT)"

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	@rm -f $(NAME)
	@echo "$(RED)all deleted!$(DEFAULT)"

re: fclean all

.PHONY: all re clean fclean subsystems
