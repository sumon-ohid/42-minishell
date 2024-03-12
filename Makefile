NAME = minishell
CC = cc
CC1 = clang
CC2 = gcc
CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=address
HEADER = minishell.h

#Colors
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m
RESET = \033[0m

SRC = 	srcs/main/main.c \
		srcs/main/prepare_env.c \
		srcs/main/ft_free.c \
		srcs/main/ft_free2.c \
		srcs/main/handle_error.c \
		srcs/parsing/lexer.c \
		srcs/parsing/mole_parser.c\
		srcs/parsing/mole_breakertokens.c\
		srcs/parsing/mole_soft_tokens.c\
		srcs/parsing/create_tokens.c\
		srcs/parsing/tokenize_values.c\
		srcs/parsing/env_expander.c\
		srcs/parsing/token_helpers.c\
		srcs/executions/cmd1_init_and_fork.c \
		srcs/executions/cmd2_execute_chain.c \
		srcs/executions/cmd3_builtins.c \
		srcs/executions/pipex.c \
		srcs/executions/waiting.c \
		srcs/executions/redirects.c \
		srcs/executions/redirects_extra.c \
		srcs/builtins/ft_cd.c \
		srcs/builtins/cd_extra.c \
		srcs/builtins/ft_echo.c \
		srcs/builtins/ft_echo_extra.c \
		srcs/builtins/ft_env.c \
		srcs/builtins/ft_export.c \
		srcs/builtins/ft_export_extra.c \
		srcs/builtins/ft_pwd.c \
		srcs/builtins/ft_unset.c \
		srcs/builtins/ft_exit.c \
		srcs/heredoc/heredoc.c \
		srcs/heredoc/heredoc_extra.c \
		srcs/signals/signals.c \
		srcs/signals/ft_lastvalue.c \
		srcs/utils/libft_helpers.c \
		srcs/utils/libft_helpers1.c \
		srcs/utils/libft_helpers2.c \
		srcs/utils/libft_helpers3.c \
		srcs/utils/libft_helpers4.c \
		srcs/utils/libft_helpers5.c \
		srcs/utils/ft_split.c \
		srcs/utils/ft_atoi.c \
		srcs/utils/ft_itoa.c \
		srcs/utils/ft_split_special_edition.c \
		srcs/utils/ft_split_extra.c \
		srcs/utils/ft_printerr.c \
		

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lreadline
	@echo "$(GREEN)Executable $(NAME) created!$(DEF_COLOR)"

clean:
	@rm -f $(OBJ) $(BN_OBJ)
	@echo "$(YELLOW) Object files removed. $(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(YELLOW) $(NAME) file removed. $(RESET)"

smooth: all clean

re:
	@$(MAKE) fclean
	@$(MAKE) all

celan:
	@echo "$(YELLOW)Lol, that's not quite what you wanted to write, huh?$(DEF_COLOR)"
	
fcelan: celan

clear: celan

strict:
	@echo "$(GREEN)Compiling with $(YELLOW)$(CC1)$(GREEN)...$(DEF_COLOR)"
	@$(MAKE) all CC=$(CC1)
	@echo "$(GREEN)Cleaning up...$(DEF_COLOR)"
	@$(MAKE) fclean
	@echo "$(GREEN)Compiling with $(YELLOW)$(CC2)$(GREEN)...$(DEF_COLOR)"
	@$(MAKE) all CC=$(CC2)
	@echo "$(GREEN)Cleaning up again...$(DEF_COLOR)"
	@$(MAKE) clean
	@echo "$(GREEN)Tested for both compilers.$(DEF_COLOR)"

.PHONY: all clean fclean re bonus strict smooth celan fcelan clear
