# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asaracut <asaracut@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/15 20:59:12 by asaracut          #+#    #+#              #
#    Updated: 2025/11/23 02:37:19 by asaracut         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program configuration
NAME		= cube3d
SRCS		= src/main.c\
			  src/parsing/parsing.c src/parsing/parsing_outil.c\
			  src/parsing/stock_info.c src/parsing/stock_map.c\
			  src/parsing/stock_texture.c\
			  src/exit_free/error_exit.c src/exit_free/exit_free.c\
			  src/utils/utils_lib.c\
			  src/utils/get_next_line.c
OBJS		= $(SRCS:src/%.c=.obj/%.o)
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3
INCLUDES	= -Iinclude

# Colors and emojis for pretty output
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
RED			= \033[0;31m
BLUE		= \033[0;34m
PURPLE		= \033[0;35m
CYAN		= \033[0;36m
WHITE		= \033[0;37m
RESET		= \033[0m
BOLD		= \033[1m

# Progress counter
TOTAL_FILES	= $(words $(SRCS))
COMPILED	= 0

all: header
	@if [ -f $(NAME) ] && [ $(NAME) -nt $(firstword $(SRCS)) ]; then \
		echo "$(GREEN)$(BOLD)"; \
		echo "╔══════════════════════════════════════════════════════════════╗"; \
		echo "║                   ✅ ALREADY UP TO DATE! ✅                  ║"; \
		echo "║                   🎯 Nothing to compile 🎯                   ║"; \
		echo "╚══════════════════════════════════════════════════════════════╝"; \
		echo "$(RESET)"; \
	else \
		$(MAKE) --no-print-directory $(NAME); \
	fi

$(NAME): $(OBJS)
	@echo "$(GREEN)🔗 Linking executable $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "$(GREEN)$(BOLD)"
	@echo "╔══════════════════════════════════════════════════════════════╗"
	@echo "║                   ✅ COMPILATION SUCCESS! ✅                 ║"
	@echo "║                     🎉 Cube3D is ready! 🎉                   ║"
	@echo "╚══════════════════════════════════════════════════════════════╝"
	@echo "$(RESET)"

header:
	@echo "$(CYAN)$(BOLD)"
	@echo "╔══════════════════════════════════════════════════════════════╗"
	@echo "║                         🎮 CUBE3D 🎮                         ║"
	@echo "║                     Compilation started                      ║"
	@echo "║                    made by Andrei & Resul                    ║"
	@echo "╚══════════════════════════════════════════════════════════════╝"
	@echo "$(RESET)"

# Create object directory
.obj:
	@mkdir -p .obj
	@echo "$(BLUE)📁 Creating object directory...$(RESET)"

# Compile object files
.obj/%.o: src/%.c | .obj
	@$(eval COMPILED=$(shell echo $$(($(COMPILED)+1))))
	@echo "$(YELLOW)🔨 Compiling [$(COMPILED)/$(TOTAL_FILES)] $<...$(RESET)"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)🧹 Cleaning object files...$(RESET)"
	@rm -rf .obj
	@echo "$(RED)✨ Object files cleaned!$(RESET)"

fclean: clean
	@echo "$(RED)🗑️  Removing executable $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@echo "$(RED)💥 Full clean completed!$(RESET)"

re: fclean all

.PHONY: all clean fclean re header