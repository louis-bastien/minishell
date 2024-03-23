# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/06 14:39:27 by agheredi          #+#    #+#              #
#    Updated: 2024/03/23 15:57:50 by lbastien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAGS = -Wall -Werror -Wextra -g #-fsanitize='address,undefined'
SRC = srcs/main.c \
	srcs/minishell.c \
	srcs/init.c \
	srcs/signals.c \
	srcs/error/error.c \
	srcs/error/reset.c \
	srcs/error/free.c \
	srcs/error/close_heredoc.c \
	srcs/error/error_builtins.c \
	srcs/lexer/lexer.c \
	srcs/lexer/char_checker.c \
	srcs/lexer/char_handler.c \
	srcs/lexer/tokens.c \
	srcs/expander/expander.c \
	srcs/expander/env_variables.c \
	srcs/expander/quotes.c \
	srcs/parser/parser.c \
	srcs/parser/redirections.c \
	srcs/parser/args.c \
	srcs/parser/redirecheredoc.c \
	srcs/utils/path.c \
	srcs/utils/cmd.c \
	srcs/utils/print.c \
	srcs/utils/get_var_envp.c \
	srcs/utils/env.c \
	srcs/utils/free_darray.c \
	srcs/utils/ft_strcmp.c \
	srcs/utils/miniexport_utils.c \
	srcs/executor/pipes.c \
	srcs/executor/executor.c \
	srcs/executor/ft_execve.c \
	srcs/builtins/ft_builtins.c \
	srcs/builtins/minicd.c \
	srcs/builtins/minipwd.c \
	srcs/builtins/minienv.c \
	srcs/builtins/miniecho.c \
	srcs/builtins/miniexit.c \
	srcs/builtins/miniexport.c \
	srcs/builtins/miniunset.c \

HEADER = includes/minishell.h \
		includes/funct.h \
		includes/lib.h \
		includes/struct.h \
		includes/var.h

#Local libraries
LIBFT_PATH = libft/
LIBFT_LIB = -lft

READLINE_PATH = readline-8.1/
READLINE_LIB = -lreadline -lhistory

LIBS = $(LIBFT_LIB) $(READLINE_LIB) -lncurses
LIB_FLAGS = -L $(LIBFT_PATH) -L $(READLINE_PATH)

READLINE_ABSOLUTE_PATH = $(shell pwd)/readline-8.1

#Objects
OBJ_DIR = obj
OBJECTS = $(addprefix $(OBJ_DIR)/,$(notdir $(SRC:.c=.o)))

INCLUDES = -I includes -I $(LIBFT_PATH) -I $(READLINE_PATH)

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

$(OBJ_DIR)/%.o: srcs/expander/%.c $(HEADER) Makefile
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

$(OBJ_DIR)/%.o: srcs/builtins/%.c $(HEADER) Makefile
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
