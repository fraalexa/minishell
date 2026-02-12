# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bepinhei <bepinhei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/25 20:49:55 by bepinhei          #+#    #+#              #
#    Updated: 2025/10/25 20:49:55 by bepinhei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -rf

# Paths
SRC_DIR		= src
INC_DIR		= includes
OBJ_DIR		= obj
LIBFT_DIR	= lib/libft
LIBFT		= $(LIBFT_DIR)/libft.a

# Includes
INCLUDES	= -I$(INC_DIR) -I$(LIBFT_DIR)

# Sources - all .c files in src directory
SRCS = \
	main/main.c \
	main/init.c \
	main/init_vars.c \
	main/prompt.c \
	main/shell_loop.c \
	main/loop_functions.c \
	main/loop_helpers.c \
	main/command_utils.c \
	lexer/lexer.c \
	lexer/lexer_utils.c \
	lexer/lexer_operators.c \
	lexer/lexer_word.c \
	lexer/token_utils.c \
	lexer/misc_utils.c \
	lexer/expander.c \
	lexer/expander_utils.c \
	lexer/expander_helpers.c \
	lexer/expander_ast.c \
	lexer/expander_vars.c \
	parser/parser.c \
	parser/parser_utils.c \
	parser/parser_utils2.c \
	parser/parser_syntax.c \
	parser/parser_helper.c \
	parser/parser_helpers.c \
	parser/args_utils.c \
	parser/syntax_utils.c \
	parser/memory_utils.c \
	executor/executor_utils.c \
	executor/execute_utils.c \
	executor/signals.c \
	executor/signal_executor.c \
	executor/execute_ast.c \
	executor/execute_redirect.c \
	executor/execute_builtins.c \
	executor/execute_redirections.c \
	executor/execute_pipes.c \
	builtins/echo.c \
	builtins/cd.c \
	builtins/pwd.c \
	builtins/export.c \
	builtins/export_vars.c \
	builtins/export_utils.c \
	builtins/export_utils2.c \
	builtins/unset.c \
	builtins/env.c \
	builtins/exit.c \
	builtins/exit_utils.c \
	utils/memory.c \
	utils/memory_parser.c \
	utils/file_descriptors.c \
	utils/string_utils.c

# Object files - convert path/file.c to obj/path/file.o
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Suppression file content
define SUP_BODY
{
	name
	Memcheck:Leak
	fun:*alloc
	...
	obj:*/libreadline.so.*
	...
}
{
	leak readline
	Memcheck:Leak
	...
	fun:readline
}
{
	leak add_history
	Memcheck:Leak
	...
	fun:add_history
}
endef

# Rules
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

# Create object files from source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		echo "Cloning Zicomora's libft..."; \
		git clone https://github.com/Zico-Moras/42-libft.git $(LIBFT_DIR); \
	fi
	@make -C $(LIBFT_DIR)

sup:
	$(file > sup,$(SUP_BODY))

clean:
	@echo "Cleaning object files..."
	@$(RM) $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@echo "Removing $(NAME)..."
	@$(RM) $(NAME)
	@if [ -d "$(LIBFT_DIR)" ]; then \
		make -C $(LIBFT_DIR) fclean; \
	fi

re: fclean all

.PHONY: all clean fclean re sup
