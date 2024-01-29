# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/06 14:39:27 by agheredi          #+#    #+#              #
#    Updated: 2024/01/29 14:54:29 by agheredi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAGS = -Wall -Werror -Wextra -g #-fsanitize='address,undefined'
SRC = srcs/main.c \


CC = gcc
LIBFT_PATH = libft/
LIBFT_LIB = $(LIBFT_PATH)libft.a
OBJ_DIR = obj
OBJECTS = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
HEADER = minishell.h

# Colores
GREEN = \033[0;32m
YELLOW = \033[1;33m
RED = \033[0;31m
DEFAULT = \033[0m

all: subsystems $(NAME)

$(OBJ_DIR)/%.o: %.c $(HEADER) Makefile
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) -c -o $@ $<

$(OBJS_DIR_BONUS)/%.o: %.c $(HEADER_BONUS) Makefile
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -c -o $@ $<

subsystems:
	@make -C $(LIBFT_PATH) all

$(NAME): $(OBJECTS)
	@$(CC) $(FLAGS) $(OBJECTS) $(LIBFT_LIB) -o $(NAME)
	@echo -e "$(GREEN)$(NAME) created!$(DEFAULT)"

clean_bonus:
	@make -C $(LIBFT_PATH) clean
	@rm -rf $(OBJS_DIR_BONUS)
	@echo -e "$(YELLOW)bonus object files deleted!$(DEFAULT)"

clean: clean_bonus
	@make -C $(LIBFT_PATH) clean
	@rm -rf $(OBJ_DIR)
	@echo -e "$(YELLOW)object files deleted!$(DEFAULT)"

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	@rm -f $(NAME)
	@echo -e "$(RED)all deleted!$(DEFAULT)"

re: fclean all

.PHONY: all re clean fclean subsystems 
